//
// Created by 范軒瑋 on 2019-09-25.
//

#ifndef CPP_LOGGER_COLOR_H
#define CPP_LOGGER_COLOR_H

#include <string>

namespace utils {

namespace {
std::ostream& __base(std::ostream& stream, std::string identifier) {
    stream << identifier;
    return stream;
}
}  // unnamed namespace

#define BLACK_TEXT(x) "\033[30;1m" x "\033[0m"
#define RED_TEXT(x) "\033[31;1m" x "\033[0m"
#define GREEN_TEXT(x) "\033[32;1m" x "\033[0m"
#define YELLOW_TEXT(x) "\033[33;1m" x "\033[0m"
#define BLUE_TEXT(x) "\033[34;1m" x "\033[0m"
#define MAGENTA_TEXT(x) "\033[35;1m" x "\033[0m"
#define CYAN_TEXT(x) "\033[36;1m" x "\033[0m"
#define WHITE_TEXT(x) "\033[37;1m" x "\033[0m"

#define BOLD_BLACK_TEXT(x) "\033[1m\033[30m;1m" x "\033[0m"
#define BOLD_RED_TEXT(x) "\033[1m\033[31m;1m" x "\033[0m"
#define BOLD_GREEN_TEXT(x) "\033[1m\033[32m;1m" x "\033[0m"
#define BOLD_YELLOW_TEXT(x) "\033[1m\033[33m;1m" x "\033[0m"
#define BOLD_BLUE_TEXT(x) "\033[1m\033[34m;1m" x "\033[0m"
#define BOLD_MAGENTA_TEXT(x) "\033[1m\033[35m;1m" x "\033[0m"
#define BOLD_CYAN_TEXT(x) "\033[1m\033[36m;1m" x "\033[0m"
#define BOLD_WHITE_TEXT(x) "\033[1m\033[37m;1m" x "\033[0m"

}  // namespace utils

#endif  // CPP_LOGGER_COLOR_H
