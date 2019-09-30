/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * A simple progress bar that needs manual updating,
 * with dynamic window filling width control
 */

#ifndef CPP_LOGGER_PROGRESSBAR_H
#define CPP_LOGGER_PROGRESSBAR_H

#include <sys/ioctl.h>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "./utils/color.h"

namespace logging {

class ProgressBar {
   private:
    static int nbars;

   private:
    const std::string description;
    const int total;
    int current_num;
    const int position;
    int last_print_len;

   private:
    inline float percentage();
    int __digits(int number);
    int window_width();
    void moveto(const int n);
    void fill_screen(const std::string s);

   public:
    ProgressBar(const std::string& description, const int total,
                const int initial, const int position);
    ProgressBar(const std::string& description, const int total);
    ~ProgressBar();
    void update(int delta = 1);
};

}  // namespace logging

#endif  // CPP_LOGGER_PROGRESSBAR_H
