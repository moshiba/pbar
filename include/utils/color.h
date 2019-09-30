//
// Created by 范軒瑋 on 2019-09-25.
//

#ifndef CPP_LOGGER_COLOR_H
#define CPP_LOGGER_COLOR_H

#ifndef __APPLE__
#error unsupported platform
#endif

#include <iostream>
#include <string>

namespace utils {

inline std::ostream& reset(std::ostream& stream) {
    stream << "\033[00m";
    return stream;
}

namespace color {

inline std::ostream& red(std::ostream& stream) {
    stream << "\033[31m";
    return stream;
}
inline std::ostream& black(std::ostream& stream) {
    stream << "\033[30m";
    return stream;
}
inline std::ostream& green(std::ostream& stream) {
    stream << "\033[32m";
    return stream;
}
inline std::ostream& yellow(std::ostream& stream) {
    stream << "\033[33m";
    return stream;
}
inline std::ostream& blue(std::ostream& stream) {
    stream << "\033[34m";
    return stream;
}
inline std::ostream& magenta(std::ostream& stream) {
    stream << "\033[35m";
    return stream;
}
inline std::ostream& cyan(std::ostream& stream) {
    stream << "\033[36m";
    return stream;
}
inline std::ostream& white(std::ostream& stream) {
    stream << "\033[37m";
    return stream;
}

}  // namespace color

namespace style {

inline std::ostream& bold(std::ostream& stream) {
    stream << "\033[1m";
    return stream;
}

inline std::ostream& dark(std::ostream& stream) {
    stream << "\033[2m";
    return stream;
}

inline std::ostream& italic(std::ostream& stream) {
    stream << "\033[3m";
    return stream;
}

inline std::ostream& underline(std::ostream& stream) {
    stream << "\033[4m";
    return stream;
}

inline std::ostream& blink(std::ostream& stream) {
    stream << "\033[5m";
    return stream;
}

inline std::ostream& reverse(std::ostream& stream) {
    stream << "\033[7m";
    return stream;
}

inline std::ostream& concealed(std::ostream& stream) {
    stream << "\033[8m";
    return stream;
}

inline std::ostream& crossed(std::ostream& stream) {
    stream << "\033[9m";
    return stream;
}

}  // namespace style

}  // namespace utils

#endif  // CPP_LOGGER_COLOR_H
