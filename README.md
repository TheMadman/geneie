# Geneie - A Library and Tools for Gene Processing

Geneie is a small, simple C library for gene processing.

## Building

This library uses CMake for building and has the following
dependency:

- libadt - https://github.com/TheMadman/libadt/tree/master

Tests may include additional dependencies in the future,
but for now they are simple C programs.

```bash
mkdir build
pushd build

# -DBUILD_TESTING=True and -DBUILD_EXAMPLES=True are optional
cmake -DBUILD_TESTING=True -DBUILD_EXAMPLES=True ..
make

# make test will only work with -DBUILD_TESTING=True
# If any tests fail, please report it as a bug!
make test
popd
```

## Documentation

The main documentation and examples can be found here:
https://themadman.github.io/geneie/index.html

The example programs are built when cmake is configured with
`-DBUILD_EXAMPLES=True`.

Missing, confusing or unclear documentation is considered a
bug. Please report it!
