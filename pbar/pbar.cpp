/*
 * Base class of the progress bar
 * Copyright (C) 2019  Hsuan-Ting Lu, 范軒瑋
 *
 * GNU General Public License v3.0+
 * (see LICENSE or https://www.gnu.org/licenses/)
 */

#include "pbar.hpp"

#include <unistd.h>

#include <algorithm>
#include <iomanip>
#include <iostream>

namespace pbar {

std::mutex ProgressBar::class_mutex;
std::vector<ProgressBar*> ProgressBar::bar_registry;

void ProgressBar::update_positions() {
    for (unsigned int i = 0; i != ProgressBar::bar_registry.size(); ++i) {
        ProgressBar::bar_registry[i]->position = i;
    }
}

ProgressBar::ProgressBar(const std::string& description, const long long& total,
                         const bool leave, const int width,
                         const std::chrono::nanoseconds min_interval_time,
                         const std::string& bar_format,
                         const long long& initial_value, const int position)
    : initial_value(initial_value),
      description(description),
      total(total),
      leave(leave),
      min_interval_time(min_interval_time),
      min_interval_iter(1),
      bar_format(bar_format.empty()
                     ? "{desc}: {percentage:3.2f}|{progress}| {n}/{total}"
                     : bar_format),
      n(initial_value),
      position(position),
      last_update_n(initial_value),
      last_update_time(std::chrono::system_clock::now()),
      disable(false) {
    if (width > 0) {
        this->window_width = [width]() -> int { return width; };
    } else {
        this->window_width = []() -> int {
            winsize
                window_size;  // TODO: save this reallocation, hide it in class
            ioctl(STDERR_FILENO, TIOCGWINSZ, &window_size);
            return static_cast<int>(window_size.ws_col);
        };
    }

    {
        std::lock_guard<std::mutex> guard(ProgressBar::class_mutex);
        ProgressBar::bar_registry.emplace(
            ProgressBar::bar_registry.begin() + position, this);
        ProgressBar::update_positions();
    }

    this->display();
}

ProgressBar::ProgressBar(const std::string& description, const long long& total,
                         const bool leave)
    : ProgressBar(description, total, leave, -1,
                  std::chrono::duration_cast<std::chrono::nanoseconds>(
                      std::chrono::milliseconds(10)),
                  "", 0, ProgressBar::bar_registry.size()) {}

ProgressBar::~ProgressBar() { this->close(); }

inline float ProgressBar::percentage() {
    // TODO: deprecate and merge
    return static_cast<float>(this->n) / this->total * 100.0;
}

int ProgressBar::__digits(long long number) {
    int digits;
    if (number == 0) {
        return 1;
    }
    for (digits = 0; number; ++digits) {
        number /= 10;
    }
    return digits;
}

void ProgressBar::moveto(const int n) {
    /** Moves the cursor vertically,
     *
     * goes up if `n` is negative,
     * goes down otherwise.
     */

    if (n > 0) {
        // moves down, needs NEWLINE to actually create and move to lines below
        for (int i = 0; i != n; ++i) {
            std::cout << "\n";
        }
    } else {
        // moves up
        std::cout << "\033[" << -n << "A";
    }
}

void ProgressBar::fill_screen(const std::string& s) {
    /* Clears the entire line,
     *  resets cursor to the beginning position,
     *  then print the designated string.
     */
    std::ios coutstate(nullptr);
    coutstate.copyfmt(std::cout);
    std::cout << "\033[2K\r" << s;
    std::cout.copyfmt(coutstate);
}

std::string ProgressBar::format_meter() {
    // TODO: doesn't support custom format yet
    /** Returns a formatted progress bar in string format
     */
    // TODO: add another function to pre-format some parts upon "description"
    // change can achieve custom format while keeping efficiency
    int bar_width = this->window_width() - this->__digits(this->n) -
                    this->__digits(this->total) - 12;
    std::ostringstream fstring;
    fstring << "\033[0m";

    // Inject left metadata
    if (!this->description.empty()) {
        fstring << this->description + ": ";
        bar_width -= this->description.length() + 2;
    }
    fstring << std::fixed << std::setw(6) << std::setprecision(2);
    fstring << this->percentage() << "%"
            << "\033[31m"
            << "|"
            << "\033[0m";

    // Inject running-bar
    int processed = bar_width * this->n / this->total;
    int remaining = bar_width - processed;

    if (bar_width > 0) {
        for (int i = processed; i != 0; --i) {
            fstring << "█";
        }
        for (int i = remaining; i != 0; --i) {
            fstring << " ";
        }
    }

    // Inject right metadata
    fstring << "\033[31m"
            << "|"
            << "\033[0m"
            << " " << this->n << "/" << this->total << " ";

    return fstring.str();
}

void ProgressBar::display() {
    /** Refresh display of this bar
     */
    const std::lock_guard<std::mutex> guard(this->pbar_mutex);

    if (this->position) {
        this->moveto(this->position);
    }

    this->fill_screen(this->format_meter());
    // std::cout << std::flush;  // TODO: investigate if this is needed

    if (this->position) {
        this->moveto(-this->position);
    }
    std::cout << std::flush;
}

const std::chrono::nanoseconds ProgressBar::delta_time(
    std::chrono::time_point<std::chrono::system_clock>& now) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        now - this->last_update_time);
}

inline long ProgressBar::delta_iter() {
    return static_cast<long>(this->n - this->last_update_n);
}

void ProgressBar::update(const int n) {
    if (this->disable) {
        return;
    }

    // HACK: for auto-refresh logic to work
    if (n < 0) {
        this->last_update_n += n;
    }
    this->n += n;
    // BUG: TODO: consider last_print_n when n < 0

    // check delta-iter to reduce calls to clock::now()
    long delta_iters(std::move(this->delta_iter()));
    if (delta_iters >= this->min_interval_iter) {
        // check delta-time
        std::chrono::time_point<std::chrono::system_clock> now =
            std::chrono::system_clock::now();
        if (this->delta_time(now) > this->min_interval_time) {
            this->display();

            // TODO: find better dynamic min_interval_iter adjustments, might
            // want to consider interval fluctuation Uses max number of
            // iterations between two updates
            this->min_interval_iter =
                std::max(this->min_interval_iter, delta_iters);
            // TODO: how to evaluate this guess on next round

            // Store old values for next call
            {
                std::lock_guard<std::mutex> guard(this->pbar_mutex);
                // this->last_update_n = this->n;
                const long long tmp = this->n.load();
                this->last_update_n = tmp;

                this->last_update_time = std::move(now);
            }
        }
    }
}

void ProgressBar::close() {
    /* Clean up visuals, closes pbar if set not to leave it
     * then resets
     */
    if (this->disable) {
        return;
    }
    // Prevent multiple closures
    this->disable = true;

    // Remove pbar from record
    ProgressBar::bar_registry.erase(std::find(ProgressBar::bar_registry.begin(),
                                              ProgressBar::bar_registry.end(),
                                              this));
    // TODO: WIP: implement internal set instead of simple counting to maintain
    // multi-bar order
    // delete window_width; TODO: FIXME

    this->display();
    // TODO: write final stats

    if (this->leave) {
        // leave this bar as it is
    } else {
        // close (clean up) the pbar
        const std::lock_guard<std::mutex> guard(this->pbar_mutex);

        this->moveto(this->position);
        std::cout << "\r"
                  << "\033[0K";
        this->moveto(-this->position);
    }
}

void ProgressBar::reset() {
    /* encourages repeated use
     */
    this->n = this->initial_value;
    this->last_update_n = this->initial_value;
    this->last_update_time = std::chrono::system_clock::now();
    this->display();
}

ProgressBar& ProgressBar::operator+=(const int n) {
    this->update(n);
    return *this;
}

ProgressBar& ProgressBar::operator-=(const int n) {
    this->update(-n);
    return *this;
}

// prefix
ProgressBar& ProgressBar::operator++() {
    this->update(1);
    return *this;
}

// prefix
ProgressBar& ProgressBar::operator--() {
    this->update(-1);
    return *this;
}

}  // namespace pbar
