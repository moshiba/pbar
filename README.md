# pbar  ![GitHub](https://img.shields.io/github/license/hsuantinglu/pbar) ![GitHub release (latest SemVer including pre-releases)](https://img.shields.io/github/v/release/HsuanTingLu/pbar?include_prereleases)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/HsuanTingLu/pbar)

Low overhead C++ progress bar

## Requirements

- C++11 or higher
- [Ansi-Escape](https://github.com/HsuanTingLu/ansi-escape) library for terminal render control
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
