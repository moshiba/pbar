//
// Created by 范軒瑋 on 2019-09-25.
//

#ifndef CPP_LOGGER_PROCESSBAR_H
#define CPP_LOGGER_PROCESSBAR_H

#include <sys/ioctl.h>
#include <unistd.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

namespace logging {

class ProcessBar {
   private:
    std::string description;
    int max_num;
    int cur_num;

   private:
    inline float percentage();
    template <class T>
    int __digits(T number);
    int window_width();

   public:
    ProcessBar(const std::string description, const int max_num,
               const int init_num);
    ProcessBar(const std::string description, const int max_num);
    void update(int delta = 1);
};

}  // namespace logging

#endif  // CPP_LOGGER_PROCESSBAR_H
