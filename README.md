# tlib

[![Build and test](https://github.com/kwsp/tlib/actions/workflows/build.yml/badge.svg)](https://github.com/kwsp/tlib/actions/workflows/build.yml)

My implementations of popular data structures in C++14 for fun and for educational purposes. It's header only and aims to be mostly compatible with the C++ standard library.

## Testing

This project uses GoogleTest. CMake will pull GoogleTest from source so there's no need to install GTest with a package manager. To build tests:

```
cd test
cmake -B build
cmake --build build -j
```

To run tests, `cd build` and either execute the individual binaries or run all tests with `ctest`.
