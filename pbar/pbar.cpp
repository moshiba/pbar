/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * A simple progress bar that needs manual updating,
 *  with dynamic window filling width control
 */

#include "pbar.h"

#include "aesc.hpp"
#include "unistd.h"

namespace pbar {

int ProgressBar::nbars = 0;

ProgressBar::ProgressBar(const std::string& description, const int total,
                         const bool leave, const int width,
                         const std::chrono::nanoseconds min_interval_time,
                         const std::string bar_format, const int initial_value,
                         const int position)
    : description(description),
      total(total),
      leave(leave),
      min_interval_time(min_interval_time),
      n(initial_value),
      position(position),
      last_print_len(0),
      min_interval_iter(1),
      last_update_time(std::chrono::system_clock::now()),
      last_update_n(initial_value) {
    if (width > 0) {
        // set constant width
    } else {
        // use dynamic width detection
        // TODO: bind dynamic detection
    }
    if (bar_format.empty()) {
        // use default bar
    } else {
        // TODO: bind bar formatting function
    }
    ProgressBar::nbars += 1;
    this->display();
}

ProgressBar::ProgressBar(const std::string& description, const int total)
    : ProgressBar(description, total, false, -1,
                  std::chrono::duration_cast<std::chrono::nanoseconds>(
                      std::chrono::milliseconds(100)),
                  "", 0, ProgressBar::nbars) {}

ProgressBar::~ProgressBar() { ProgressBar::nbars -= 1; }

int ProgressBar::window_width() {
    winsize window_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
    return window_size.ws_col;
}

inline float ProgressBar::percentage() {
    return static_cast<float>(this->n) / this->total * 100.0;
}

int ProgressBar::__digits(long long number) {
    int digits = 0;
    if (number == 0) {
        return 1;
    }
    while (number) {
        number /= 10;
        ++digits;
    }
    return digits;
}

void ProgressBar::moveto(const int n) {
    /** Moves the cursor vertically,
     *
     * goes up if `n` is negative,
     * goes down otherwise.
     */

    // the common case is n=0, skips it for performance
    if (n == 0) {
        return;
    } else if (n > 0) {
        // moves down
        for (int i = 0; i != n; ++i) {
            std::cout << "\n";
        }
    } else {
        // moves up
        std::cout << aesc::cursor::up(-n);
    }
}

void ProgressBar::fill_screen(const std::string s) {
    /** Printing and in-place updating
     */
    std::cout << "\r" << s;
    for (int i = 0;
         i < std::max(this->last_print_len - static_cast<int>(s.length()), 0);
         i++) {
        std::cout << " ";
    }
    this->last_print_len = static_cast<int>(s.length());
}

std::string ProgressBar::format_meter() {
    /** Returns a formatted progress bar in string format
     */
    int bar_width = this->window_width() - this->__digits(this->n) -
                    this->__digits(this->total) - 12;
    std::ostringstream fstring;
    fstring << aesc::render::reset;

    // Inject left metadata
    if (!this->description.empty()) {
        fstring << this->description << ": ";
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
    fstring << aesc::color::red << "|" << aesc::render::reset << " " << this->n << "/"
            << this->total << " ";

    return fstring.str();
}

void ProgressBar::display() {
    /** Refresh display of this bar
     */
    this->moveto(this->position);

    std::ios coutstate(nullptr);
    coutstate.copyfmt(std::cout);
    this->fill_screen(this->format_meter());
    std::cout << std::flush;
    std::cout.copyfmt(coutstate);

    this->moveto(-this->position);
    std::cout << std::flush;
}

void ProgressBar::close() {
    /** Cleanup and if not top level, close the progressbar
     */
    std::cout << std::endl;
}

void ProgressBar::update(const int n) {
    this->n += n;
    // BUG: consider last_print_n when n < 0

    // check delta-iterations to reduce calls to clock::now()
    if (this->delta_iter() > this->min_interval_iter) {
        // check delta-time
        if (this->delta_time() > this->min_interval_time) {
            this->display();

            // TODO: dynamic min_interval_iter adjustments

            this->last_update_n = this->n;
            this->last_update_time = std::chrono::system_clock::now();
        }
    }
}

const std::chrono::nanoseconds ProgressBar::delta_time() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::now() - this->last_update_time);
}

int ProgressBar::delta_iter() { return this->n - this->last_update_n; }

}  // namespace pbar
