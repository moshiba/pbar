//
// Created by 范軒瑋 on 2019-09-25.
//

#include "../include/Logger.h"

namespace log {

LEVEL Logger::level = LEVEL::DEBUG;

Logger::Logger(std::string name) { this->name = name; }

void Logger::setLevel(log::LEVEL level) { Logger::level = level; }

}  // namespace log
