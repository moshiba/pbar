# pbar  ![GitHub](https://img.shields.io/github/license/hsuantinglu/pbar) ![GitHub release (latest SemVer including pre-releases)](https://img.shields.io/github/v/release/HsuanTingLu/pbar?include_prereleases)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/HsuanTingLu/pbar)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c0335227c419495fac02ce71c83c60d6)](https://www.codacy.com/manual/HsuanTingLu/pbar?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=HsuanTingLu/pbar&amp;utm_campaign=Badge_Grade)

Low overhead C++ progress bar with a friendly interface

## Table of Contents
- [Quickstart](#quickstart)
- [Requirements](#requirements)
- [Build](#build)

<a name="quickstart"></a>
## Quickstart

The `pbar` library is very easy to use,
with a simple constructor `ProgressBar(${description}, ${total})` and you're ready to go.

Updating the bar is as easy as the construction process, `update(${number})` increases/decreases the bar to whatever number you want.

there are example codes in the `examples/` directory, see [Build](#build) for more information.

### Simple example
```cpp
#include "pbar.hpp"
using namespace pbar;

int main() {
    ProgressBar progressbar("outer", 10);
    for (int i = 0; i != 10; ++i) {
        progressbar.update();
    }
}
```

### Nested progress bars
```cpp
#include "pbar.hpp"
using namespace pbar;
constexpr int test_size1 = 10;
constexpr int test_size2 = 10000000;

int main() {
    ProgressBar progressbar1("outer", test_size1, true);
    for (int i = 0; i != test_size1; ++i) {
        ProgressBar progressbar2("inner", test_size2, true);
        for (int j = 0; j != test_size2; ++j) {
            progressbar2.update();
        }
        progressbar1.update();
    }
}
```

<a name="requirements"></a>
## Requirements

- C++11 or higher
- [Ansi-Escape](https://github.com/HsuanTingLu/ansi-escape) library for terminal render control
- CMake 3.5 or higher

<a name="build"></a>
## Build
CMake is the official build system.
At least version 3.5 is needed.

```bash
mkdir build; cd build/

# Config and build
cmake .. && make driver

# execute example
./examples/driver
```