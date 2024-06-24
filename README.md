# Geneie - A Library and Tools for Gene Processing

Geneie is a small, simple C library for gene processing.

## Building

This library uses CMake for building. Otherwise, we try to only
depend on standard C and POSIX for the library itself.

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

Documentation can be built using Doxygen.

```bash
doxygen
```

The `doxygen` command will create a `html` directory. You can
open the `html` version of the documentation from `html/index.html`.

The documentation pages and example programs in the `pages/` directory
are a useful starting place.
