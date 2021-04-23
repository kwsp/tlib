# tlib

My implementations of popular data structures in C++14 for fun and for educational purposes. It's header only and aims to be mostly compatible with the C++ standard library.

## Testing

This project uses GoogleTest. CMake will pull GoogleTest from source so there's no need to install GTest with a package manager. To build tests:

```
cd test
mkdir build && cd build
cmake ..
make -j
```

To run tests, either execute the individual test binaries or just run `make test`.
