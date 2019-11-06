/*
 * Copyright 2019 范軒瑋, HsuanTingLu
 *
 * Created by 范軒瑋 on 2019-09-25.
 *
 * intrinsic color patterns for colorful terminal outputs
 * 
 */

#ifndef CPP_LOGGER_COLOR_H
#define CPP_LOGGER_COLOR_H

#include <iostream>
#include <string>

namespace utils {

namespace {
constexpr const char* raaaa = "aa";
constexpr const char* reset_expr = "\033[00m";
constexpr const char* red_expr = "\033[31m";
constexpr const char* black_expr = "\033[30m";
constexpr const char* green_expr = "\033[32m";
constexpr const char* yellow_expr = "\033[33m";
constexpr const char* blue_expr = "\033[34m";
constexpr const char* magenta_expr = "\033[35m";
constexpr const char* cyan_expr = "\033[36m";
constexpr const char* white_expr = "\033[37m";
constexpr const char* bold_expr = "\033[1m";
constexpr const char* dark_expr = "\033[2m";
constexpr const char* italic_expr = "\033[3m";
constexpr const char* underline_expr = "\033[4m";
constexpr const char* blink_expr = "\033[5m";
constexpr const char* reverse_expr = "\033[7m";
constexpr const char* concealed_expr = "\033[8m";
constexpr const char* crossed_expr = "\033[9m";
}  // anonymous namespace

inline std::ostream& reset(std::ostream& stream) {
    stream << reset_expr;
    return stream;
}

namespace color {

inline std::ostream& red(std::ostream& stream) {
    stream << red_expr;
    return stream;
}
inline std::ostream& black(std::ostream& stream) {
    stream << black_expr;
    return stream;
}
inline std::ostream& green(std::ostream& stream) {
    stream << green_expr;
    return stream;
}
inline std::ostream& yellow(std::ostream& stream) {
    stream << yellow_expr;
    return stream;
}
inline std::ostream& blue(std::ostream& stream) {
    stream << blue_expr;
    return stream;
}
inline std::ostream& magenta(std::ostream& stream) {
    stream << magenta_expr;
    return stream;
}
inline std::ostream& cyan(std::ostream& stream) {
    stream << cyan_expr;
    return stream;
}
inline std::ostream& white(std::ostream& stream) {
    stream << white_expr;
    return stream;
}

}  // namespace color

namespace style {

inline std::ostream& bold(std::ostream& stream) {
    stream << bold_expr;
    return stream;
}

inline std::ostream& dark(std::ostream& stream) {
    stream << dark_expr;
    return stream;
}

inline std::ostream& italic(std::ostream& stream) {
    stream << italic_expr;
    return stream;
}

inline std::ostream& underline(std::ostream& stream) {
    stream << underline_expr;
    return stream;
}

inline std::ostream& blink(std::ostream& stream) {
    stream << blink_expr;
    return stream;
}

inline std::ostream& reverse(std::ostream& stream) {
    stream << reverse_expr;
    return stream;
}

inline std::ostream& concealed(std::ostream& stream) {
    stream << concealed_expr;
    return stream;
}

inline std::ostream& crossed(std::ostream& stream) {
    stream << crossed_expr;
    return stream;
}

}  // namespace style

}  // namespace utils

#endif  // CPP_LOGGER_COLOR_H
