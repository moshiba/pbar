//
// Created by 范軒瑋 on 2019-09-25.
//

#ifndef CPP_LOGGER_PROCESSBAR_H
#define CPP_LOGGER_PROCESSBAR_H

#include <string>
#include <cstring>
#include <cstdio>

namespace log{

class ProcessBar {
private:
    std::string description;
    std::string divider;
    int max_num;
    int cur_num;
    float percentage();
public:
    ProcessBar(std::string description, int max_num);
    void update(int delta = 1);
};

}

#endif //CPP_LOGGER_PROCESSBAR_H
