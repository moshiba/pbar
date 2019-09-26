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
    std::string divider;
    int max_num;
    int cur_num;
    inline float percentage();
    int window_width;
    template <class T>
    int __digits(T number);

   public:
    ProcessBar(std::string description, int max_num);
    void update(int delta = 1);
};

}  // namespace logging

#endif  // CPP_LOGGER_PROCESSBAR_H
