/*
 * Base class of the progress bar
 * Copyright (C) 2019  Hsuan-Ting Lu
 *
 * GNU General Public License v3.0+
 * (see LICENSE or https://www.gnu.org/licenses/)
 */

#include <unistd.h>

#include <iostream>

#include "pbar.hpp"

int main() {
    constexpr int test_size = 4;
    constexpr int test_size2 = 80000;
    pbar::ProgressBar pBar("fiiirst", test_size);
    pbar::ProgressBar pBar2("secoond", test_size2, true);
    for (int i = 0; i < test_size; i++) {
        pBar2.reset();
        for (int j = 0; j < test_size2; j++) {
            pBar2.update();
            usleep(1);
        }
        pBar.update();
    }
    pBar2.close();
    pBar.close();
    std::cout << std::endl << std::endl;
    std::cout << "test driver END" << std::endl;

    return 0;
}
