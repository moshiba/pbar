//
// Created by 范軒瑋 on 2019-09-25.
//

#include "../include/ProcessBar.h"
#include "../include/color.h"
namespace log {

ProcessBar::ProcessBar(std::string description, int max_num)
    : description(description), divider(" => "), max_num(max_num), cur_num(0) {}

float ProcessBar::percentage() {
    return static_cast<float>(this->cur_num) / this->max_num * 100.0;
}

void ProcessBar::update(int delta) {
    this->cur_num += delta;
    printf("%s%s%s[%6.2f%%]\r", GREEN_TEXT("[Processing] "),
           this->description.c_str(), this->divider.c_str(),
           this->percentage());
    fflush(stdout);
}

}  // namespace log
