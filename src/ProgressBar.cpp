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

ProgressBar::ProgressBar(const std::string& description, const int total,
                         const int initial, const int position)
    : description(description),
      total(total),
      current_num(initial),
      position(position) {}

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

void ProgressBar::update(int delta) {
    this->current_num += delta;
    int bar_width = this->window_width() - this->__digits(this->current_num) -
                    this->__digits(this->total) - 12;

    std::ios coutstate(nullptr);
    coutstate.copyfmt(std::cout);
    std::cout << utils::reset;

    // print left metadata
    if (!this->description.empty()) {
        std::cout << this->description << ": ";
        bar_width -= this->description.length() + 2;
    }
    std::cout << std::fixed << std::setw(6) << std::setprecision(2);
    std::cout << this->percentage() << "%" << utils::color::red << "|"
              << utils::reset;

    // print bar
    int processed =
        round(bar_width * this->current_num / static_cast<float>(this->total));
    int remaining = bar_width - processed;

    if (bar_width > 0) {
        for (int i = processed; i != 0; --i) {
            std::cout << "█";
        }
        for (int i = remaining; i != 0; --i) {
            std::cout << " ";
        }
    }

    // print right metadata
    std::cout << utils::color::red << "|" << utils::reset << " "
              << this->current_num << "/" << this->total << " ";

    std::cout.copyfmt(coutstate);
    std::cout << "\r" << std::flush;
}

}  // namespace logging
