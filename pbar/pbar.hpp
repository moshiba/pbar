/*
 * Base class of the progress bar
 * Copyright (C) 2019  Hsuan-Ting Lu
 *
 * GNU General Public License v3.0+
 * (see LICENSE or https://www.gnu.org/licenses/)
 */

#ifndef PBAR_PBAR_HPP_
#define PBAR_PBAR_HPP_

#include <sys/ioctl.h>

#include <chrono>
#include <ratio>
#include <sstream>
#include <string>

namespace pbar {

class Bar {
   public:
    Bar();
    void refresh();
};

namespace window_width {
// Functor
class window_width {
   public:
    virtual int operator()() const;
};

class static_window_width final : public window_width {
   private:
    const int width;

   public:
    explicit static_window_width(const int width);
    int operator()() const final override;
};

class dynamic_window_width final : public window_width {
   private:
    winsize window_size;

   public:
    dynamic_window_width();
    int operator()() const final override;
};
}  // namespace window_width

class ProgressBar {
    /* Not copyable, but movable
     */
   private:
    static int nbars;  // bar count

   private:
    const std::string description;
    const long long total;
    const bool leave;
    std::chrono::nanoseconds min_interval_time;
    long min_interval_iter;
    const std::string bar_format;
    long long n;
    const int position;
    long long last_update_n;
    std::chrono::system_clock::time_point last_update_time;

   private:
    inline float percentage();
    int __digits(long long number);
    window_width::window_width* window_width;  // Functor pointer
    void moveto(const int n);
    void fill_screen(const std::string& s);
    std::string format_meter();
    void display();
    const std::chrono::nanoseconds delta_time(
        std::chrono::time_point<std::chrono::system_clock>& now);
    long delta_iter();

   public:
    explicit ProgressBar(const std::string& description, const int total,
                         const bool leave, const int width,
                         const std::chrono::nanoseconds min_interval_time,
                         const std::string& bar_format, const int initial_value,
                         const int position);
    explicit ProgressBar(const std::string& description, const int total,
                         const bool leave = (ProgressBar::nbars ? false
                                                                : true));
    ~ProgressBar();
    void update(const int n = 1);
};

}  // namespace pbar

#endif  // PBAR_PBAR_H
