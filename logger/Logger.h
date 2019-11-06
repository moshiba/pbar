/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * logging module
 *
 */

#ifndef CPP_LOGGER_LOGGER_H
#define CPP_LOGGER_LOGGER_H

#include <cstdio>
#include <iostream>
#include <string>
#include "utils/color.hpp"

namespace logging {

enum class LEVEL { DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3 };

class Logger {
   private:
    std::string name;
    static LEVEL level;

   public:
    Logger(const std::string& name = "default");
    static void setLevel(LEVEL level);
};

}  // namespace logging

#endif  // CPP_LOGGER_LOGGER_H
