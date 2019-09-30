/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * logging module
 * 
 */

#include "../include/Logger.h"

namespace logging {

LEVEL Logger::level = LEVEL::DEBUG;

Logger::Logger(std::string name) { this->name = name; }

void Logger::setLevel(logging::LEVEL level) { Logger::level = level; }

}  // namespace logging
