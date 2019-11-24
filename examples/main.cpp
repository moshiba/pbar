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
    pbar::ProgressBar* progressBar =
        new pbar::ProgressBar("fiiirst", test_size);
    for (int i = 0; i < test_size; i++) {
        pbar::ProgressBar* progressBar2 =
            new pbar::ProgressBar("secoond", test_size2, true);
        for (int j = 0; j < test_size2; j++) {
            progressBar2->update();
            usleep(1);
        }
        delete progressBar2;
        progressBar->update();
    }
    delete progressBar;
    std::cout << std::endl << std::endl;
    std::cout << "test driver END" << std::endl;

    return 0;
}
