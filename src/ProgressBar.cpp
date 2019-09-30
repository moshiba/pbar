/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * A simple progress bar that needs manual updating,
 * with dynamic window filling width control
 */

#include "../include/ProgressBar.h"

namespace logging {

int ProgressBar::nbars = 0;

ProgressBar::ProgressBar(const std::string& description, const int total,
                         const int initial, const int position)
    : description(description),
      total(total),
      current_num(initial),
      position(position),
      last_print_len(0) {
    ProgressBar::nbars += 1;
}

ProgressBar::ProgressBar(const std::string& description, const int total)
    : ProgressBar(description, total, 0, ProgressBar::nbars) {}

ProgressBar::~ProgressBar() { ProgressBar::nbars -= 1; }

int ProgressBar::window_width() {
    winsize window_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
    return window_size.ws_col;
}

inline float ProgressBar::percentage() {
    return static_cast<float>(this->current_num) / this->total * 100.0;
}

template <class T>
int ProgressBar::__digits(T number) {
    int digits = 0;
    while (number) {
        number /= 10;
        ++digits;
    }
    return digits;
}

void ProgressBar::moveto(const int n) {
    /** Moves the cursor vertically,
     *
     * goes up if `n` is positive,
     * goes down otherwise.
     */
    if (n < 0) {  // moves up
        for (int i = 0; i > n; --i) {
            std::cout << "\x1b[A";
        }
    } else {  // moves down
        for (int i = 0; i < n; ++i) {
            std::cout << "\n";
        }
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

void ProgressBar::update(int delta) {
    this->current_num += delta;
    int bar_width = this->window_width() - this->__digits(this->current_num) -
                    this->__digits(this->total) - 12;

    std::ios coutstate(nullptr);
    coutstate.copyfmt(std::cout);

    // Format progressbar info
    std::ostringstream fstring;
    fstring << utils::reset;

    // Inject left metadata
    if (!this->description.empty()) {
        fstring << this->description << ": ";
        bar_width -= this->description.length() + 2;
    }
    fstring << std::fixed << std::setw(6) << std::setprecision(2);
    fstring << this->percentage() << "%" << utils::color::red << "|"
            << utils::reset;

    // Inject running-bar
    int processed =
        round(bar_width * this->current_num / static_cast<float>(this->total));
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
    fstring << utils::color::red << "|" << utils::reset << " "
            << this->current_num << "/" << this->total << " ";

    this->fill_screen(fstring.str());
    std::cout << std::flush;

    std::cout.copyfmt(coutstate);
}

}  // namespace logging
