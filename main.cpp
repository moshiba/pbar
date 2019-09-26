//
// Created by 范軒瑋 on 2019-09-25.
//

#include <unistd.h>
#include "include/Logger.h"
#include "include/ProcessBar.h"

int main() {
    logging::ProcessBar *processBar = new logging::ProcessBar("testing", 9);
    for (int i = 0; i < 9; i++) {
        processBar->update();
        sleep(1);
    }
    return 0;
}
