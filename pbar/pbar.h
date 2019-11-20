/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * A simple progress bar that needs manual updating,
 * with dynamic window filling width control
 */

#ifndef PBAR_PBAR_H
#define PBAR_PBAR_H

#include <sys/ioctl.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ratio>
#include <sstream>
#include <string>

namespace pbar {

class Bar {
   public:
    Bar();
    void refresh();
};

class ProgressBar {
   private:
    static int nbars;  // bar count

   private:
    const std::string description;
    const long long total;
    const bool leave;
    int width;
    std::chrono::nanoseconds min_interval_time;
    long min_interval_iter;
    const std::string bar_format;
    long long n;
    const int position;
    int last_print_len;
    long long last_update_n;
    std::chrono::system_clock::time_point last_update_time;

   private:
    inline float percentage();
    int __digits(long long number);
    int window_width();
    void moveto(const int n);
    void fill_screen(const std::string s);
    std::string format_meter();
    void display();
    const std::chrono::nanoseconds delta_time();
    long delta_iter();

   public:
    explicit ProgressBar(const std::string& description, const int total,
                         const bool leave, const int width,
                         const std::chrono::nanoseconds min_interval_time,
                         const std::string bar_format, const int initial_value,
                         const int position);
    explicit ProgressBar(const std::string& description, const int total);
    ~ProgressBar();
    void update(const int n = 1);
    void close();
};

}  // namespace pbar

#endif  // PBAR_PBAR_H
