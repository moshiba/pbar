//
// Created by 范軒瑋 on 2019-09-25.
// Modified by HsuanTingLu
//

#include "../include/ProcessBar.h"
#include "../include/color.h"

namespace logging {

ProcessBar::ProcessBar(const std::string description, const int max_num,
                       const int init_num)
    : description(description), max_num(max_num), cur_num(init_num) {}

ProcessBar::ProcessBar(const std::string description, const int max_num)
    : ProcessBar(description, max_num, 0) {}

int ProcessBar::window_width() {
    winsize window_size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size);
    return window_size.ws_col;
}

inline float ProcessBar::percentage() {
    return static_cast<float>(this->cur_num) / this->max_num * 100.0;
}

template <class T>
int ProcessBar::__digits(T number) {
    int digits = 0;
    while (number) {
        number /= 10;
        ++digits;
    }
    return digits;
}

void ProcessBar::update(int delta) {
    this->cur_num += delta;
    int bar_width = this->window_width() - this->__digits(this->cur_num) -
                    this->__digits(this->max_num) - 12;

    std::ios coutstate(nullptr);
    coutstate.copyfmt(std::cout);

    // print left metadata
    if (!this->description.empty()) {
        std::cout << this->description << ": ";
        bar_width -= this->description.length() + 2;
    }
    std::cout << std::fixed << std::setw(6) << std::setprecision(2);
    std::cout << this->percentage() << "%" << RED_TEXT("|");

    // print bar
    int processed =
        round(bar_width * this->cur_num / static_cast<float>(this->max_num));
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
    std::cout << RED_TEXT("|") << " " << this->cur_num << "/" << this->max_num
              << " ";

    std::cout.copyfmt(coutstate);
    std::cout << "\r" << std::flush;
}

}  // namespace logging
