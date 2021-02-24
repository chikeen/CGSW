# Examples and Tutorials

## Introduction
The `examples` directory contains tutorials and standalone example programs 
explaining the various APIs as well as a simple use-case using CGSW.

## What is provided
The tutorial cover primarily the various scheme offered and comprise 5 documented 
examples from basic operations to more complex serialization.

The example programs provided are:

- [1_gsw_basics](1_gsw_basics.cpp)
- [2_cgsw_variant_1](2_cgsw_variant_1.cpp)
- [3_cgsw_variant_2](3_cgsw_variant_2.cpp)

More examples are expected to be released at a later date.

- [4_bootstraping](4_bootstrapping.cpp) *
- [5_PIR_application](5_PIR_application.cpp) * 

## Installation

> TODO: enable flag in examples, also amend the following `cmake [-...`.

To compile the examples, you must have CGSW already installed on your system (see [install.md](../INSTALL.md) in this 
distribution's root directory). The process is some installation and pure CMake. From `examples/build` run CMake,
```bash
cmake [-Dhelib_DIR=<directory-to-installed-HElib]>/share/cmake/helib] <directory-to-examples> ..
```

then run make from the same directory with optional number of threads using the `-j` flag for example,
```bash
make [-j<number-of-threads>]
```

The executables for each of the example programs can be found in the `bin` directory. 


## Running the examples
All examples have a help method by passing the `-h` flag, for example

```bash
./1_gsw_basics -h
```

