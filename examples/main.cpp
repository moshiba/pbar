//
// Created by 范軒瑋 on 2019-09-25.
//

#include <unistd.h>
#include <iostream>
#include "logger/Logger.h"
#include "progressbar/ProgressBar.h"
#include "utils/color.hpp"

int main() {
    constexpr int test_size = 4;
    constexpr int test_size2 = 80000;
    logging::ProgressBar* progressBar = new logging::ProgressBar("fiiirst", test_size);
    for (int i = 0; i < test_size; i++) {
        logging::ProgressBar* progressBar2 = new logging::ProgressBar("secoond", test_size2);
        for (int j = 0; j < test_size2; j++) {
            progressBar2->update();
            //sleep(1);
        }
        delete progressBar2;
        progressBar->update();
    }
    std::cout << std::endl;
    delete progressBar;
    std::cout << "test driver END" << std::endl;

    return 0;
}
