# cpp-logger

Implementations of logger, status bar, etc. in C++ to let me print out information easier.

## Requirements

- C++11 or higher
- one of the following build systems
  - CMake 3.15 or higher (should be easy to satisfy via Homebrew)
  - latest [Facebook Buck](https://buck.build)

## Test

Buckbuild

```bash
buck run //examples:testdrive
```

CMake

```bash
mkdir build; cd build/

# Config and build
cmake .. && make driver

# execute example
./examples/driver
```
