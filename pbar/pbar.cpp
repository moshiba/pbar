/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * A simple progress bar that needs manual updating,
 * with dynamic window filling width control
 */

#include "pbar.h"

namespace pbar {

int ProgressBar::nbars = 0;

ProgressBar::ProgressBar(const std::string& description, const int total,
                         const int initial, const int position)
    : description(description),
      total(total),
      current_num(initial),
      position(position),
      last_print_len(0) {
    ProgressBar::nbars += 1;
    this->display();
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

int ProgressBar::__digits(int number) {
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
     * goes up if `n` is positive,
     * goes down otherwise.
     */
    if (n > 0) {
        // moves down
        for (int i = 0; i < n; ++i) {
            std::cout << "\n";
        }
    } else {
        // moves up
        for (int i = 0; i > n; --i) {
            std::cout << "\x1b[A";
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

std::string ProgressBar::format_meter() {
    /** Returns a formatted progress bar in string format
     */
    int bar_width = this->window_width() - this->__digits(this->current_num) -
                    this->__digits(this->total) - 12;
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

void ProgressBar::update(int delta) {
    this->current_num += delta;
    this->display();
}

}  // namespace logging
