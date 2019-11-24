/*
 * Base class of the progress bar
 * Copyright (C) 2019  Hsuan-Ting Lu, 范軒瑋
 *
 * GNU General Public License v3.0+ (see LICENSE or
 * https://www.gnu.org/licenses/)
 */

#include "pbar.h"

#include <cmath>
#include <iomanip>
#include <iostream>

#include "aesc.hpp"
#include "unistd.h"

namespace pbar {

int ProgressBar::nbars = 0;

namespace window_width {
// window_width
int window_width::operator()() const { return 0; }

// static_window_width
static_window_width::static_window_width(const int width) : width(width) {}
int static_window_width::operator()() const { return this->width; }

// dynamic_window_width
dynamic_window_width::dynamic_window_width() {}
int dynamic_window_width::operator()() const {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &(this->window_size));
    return static_cast<int>(this->window_size.ws_col);
}
}  // namespace window_width

ProgressBar::ProgressBar(const std::string& description, const int total,
                         const bool leave, const int width,
                         const std::chrono::nanoseconds min_interval_time,
                         const std::string bar_format, const int initial_value,
                         const int position)
    : description(description),
      total(total),
      leave(leave),
      min_interval_time(min_interval_time),
      min_interval_iter(1),
      bar_format(bar_format.empty() ? "{desc}: {percentage:3.2f}|{progress}| {n}/{total}" : bar_format),
      n(initial_value),
      position(position),
      last_update_n(initial_value),
      last_update_time(std::chrono::system_clock::now()) {
    if (width > 0) {
        this->window_width = new window_width::static_window_width(width);
    } else {
        this->window_width = new window_width::dynamic_window_width();
    }
    ProgressBar::nbars += 1;
    this->display();
}

ProgressBar::ProgressBar(const std::string& description, const int total,
                         const bool leave)
    : ProgressBar(description, total, leave, -1,
                  std::chrono::duration_cast<std::chrono::nanoseconds>(
                      std::chrono::milliseconds(100)),
                  "", 0, ProgressBar::nbars) {}

ProgressBar::~ProgressBar() {
    this->display();
    /* Cleanup and (depends on config) close the progressbar
     */
    // TODO: think this through
    if (this->leave) {
        // leave this bar as it is
    } else {
        this->moveto(this->position);
        std::cout << "\r" << aesc::cursor::EL(aesc::cursor::clear::to_end);
        this->moveto(-this->position);
    }
    ProgressBar::nbars -= 1;
}

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
        // moves down
        for (int i = 0; i != n; ++i) {
            std::cout << "\n";
        }
    } else {
        // moves up
        std::cout << aesc::cursor::up(-n);
    }
}

void ProgressBar::fill_screen(const std::string& s) {
    /* Clears the entire line,
     *  resets cursor to the beginning position,
     *  then print the designated string.
     */
    std::ios coutstate(nullptr);
    coutstate.copyfmt(std::cout);
    std::cout << aesc::cursor::EL(aesc::cursor::clear::entire) << "\r" << s;
    std::cout.copyfmt(coutstate);
}

std::string ProgressBar::format_meter() {
    // TODO: doesn't support custom format yet
    /** Returns a formatted progress bar in string format
     */
    int bar_width = (*this->window_width)() - this->__digits(this->n) -
                    this->__digits(this->total) - 12;
    std::ostringstream fstring;
    fstring << aesc::render::reset;

    // Inject left metadata
    if (!this->description.empty()) {
        fstring << this->description + ": ";
        bar_width -= this->description.length() + 2;
    }
    fstring << std::fixed << std::setw(6) << std::setprecision(2);
    fstring << this->percentage() << "%" << aesc::color::red << "|"
            << aesc::render::reset;

    // Inject running-bar
    int processed =
        round(bar_width * this->n / static_cast<float>(this->total));
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
    fstring << aesc::color::red << "|" << aesc::render::reset << " " << this->n
            << "/" << this->total << " ";

    return fstring.str();
}

void ProgressBar::display() {
    /** Refresh display of this bar
     */
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

void ProgressBar::update(const int n) {
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

            // TODO: dynamic min_interval_iter adjustments
            this->min_interval_iter = delta_iters / 3;
            // TODO: how to evaluate this guess on next round

            this->last_update_n = this->n;
            this->last_update_time = std::move(now);
        }
    }
}

const std::chrono::nanoseconds ProgressBar::delta_time(
    std::chrono::time_point<std::chrono::system_clock>& now) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        now - this->last_update_time);
}

long ProgressBar::delta_iter() {
    return static_cast<long>(this->n - this->last_update_n);
}

}  // namespace pbar
