# Geneie - A Library and Tools for Gene Processing

Geneie is a small, simple C library for gene processing.

## Building

We use CMake for building. Otherwise, we try to only
depend on standard C and POSIX for the library itself.

Tests may include additional dependencies in the future,
but for now they are simple C programs.

```bash
mkdir build
pushd build
cmake -DBUILD_TESTING=True ..
make
make test
popd
```

## Documentation

Documentation can be built using Doxygen.

```bash
doxygen
```

The `doxygen` command will create a `html` and a `latex`
directory. You can open the `html` version of the documentation
from `html/index.html`.
