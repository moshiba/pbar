# pbar  ![GitHub](https://img.shields.io/github/license/hsuantinglu/pbar) ![GitHub release (latest SemVer including pre-releases)](https://img.shields.io/github/v/release/HsuanTingLu/pbar?include_prereleases)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/HsuanTingLu/pbar)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c0335227c419495fac02ce71c83c60d6)](https://www.codacy.com/manual/HsuanTingLu/pbar?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=HsuanTingLu/pbar&amp;utm_campaign=Badge_Grade)

Low overhead C++ progress bar,
about 60μs per iteration

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
