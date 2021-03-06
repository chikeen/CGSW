# Building and installing CGSW

The CGSW has been built and installed only on macOS Big Sur >=11.0.1 at current development stages.

There are two different ways to build and install CGSW. The first one will automatically download
all dependencies and pack the library in a relocatable folder. The second way, instead, requires the dependencies
to be installed by you and available in the system.

## General prerequisites
- GNU make >= 3.82
- git >= 1.8.3

**Linux environment:**
- g++ >= 7.3.1
- cmake >= 3.10.2

**MacOS environment:**
- Apple clang >= 11.0.0 (available with the latest Xcode for the tested versions of macOS)
- Xcode Command Line Tools (can be installed with the command `xcode-select--install` in a terminal)
- cmake >= 3.17.2 (available from [Cmake](https://cmake.org/)) or [MacPorts Project](https://www.macports.org/)
and [Homebrew](https://brew.sh/) as packages)
  
## Option 1: package build (recommended for most users)
This option bundles CGSW and its dependencis in one directory which can then be moved around freely 
on the system. 

> Not yet available, WIP

## Option 2: library build (advanced)
This option involves building CGSW on its own, linking against pre-existing dependencies(Eigen, NTL and GMP) on the system.
In this way, the CGSW library can be moved around, but its dependencies cannot, as they are absolute paths. For this option, 
you must build/install Eigen >= 3.3.9, GMP >= 6.0.0 and NTL >= 11.4.3 yourself. For details on how to do this, please see the section on 
building dependencies later. It is assumed throughout this installation option that the environment variables
`$EIGENDIR`, `$GMPDIR` and `$NTLDIR` are set to point to the installation directories of Eigen, GMP and NTL respectively.

Please note that if changing from package build to library build, it is safer to use a clean build directory.

1. Create a build directory, typically as a sibling of `src`:
```bash
cd CGSW
mkdir build
cd build
```

2. Run the cmake configuration step, specifying where to find Eigen, NTL and GMP. If not specified, system-wide
locations such as `/usr/local/lib` will be searched. To install in `/home/alice/cgsw_install`, for example:
   ```bash
   cmake  -DGMP_DIR="${GMPDIR}" -DNTL_DIR="${NTLDIR}" -DCMAKE_INSTALL_PREFIX=/home/alice/cgsw_install ..
   ```
   
3. Compile, with an optional number of threads specified(16 in this example):
```bash
make
```
or
```bash
make -j16
```

4. Run the install step, to copy the files to `$CMAKE_INSTALL_PREFIX` (in this example `/home/alice/cgsw_install`):
```bash
make install
```
of course, if the `CMAKE_INSTALL_PREFIX` was kept as the default `/usr/local` or some other system-wide path, 
step 4 may require `sudo` privileges.

## Building dependencies (for option 2)


## GMP
Many distributions come with GMP pre-installed. If not, you can install GMP as follows.
1. Download GMP from http://www.gmplib.org -- make sure that you get GMP >= 6.0.0 (current version is 6.2.0).
2. Decompress and cd into the gmp directory (e.g., `gmp-6.2.0).
3. GMP is compiled in the standard unix way:
```bash
./configure
make
sudo make install
```
This will install GMP into `/usr/local` by default.

**EXTRAS**: For mac users, again you can easily do `brew install gmp` instead of all the steps above.
**NOTE**: For further options when building GMP, run `./configure --help` in step 3.

## NTL
You can install NTL as follows:
1. Download NTL >= 11.4.3 (current version is 11.4.3) from http://www.shoup.net/ntl/download.html
2. Decompress and cd into the directory, e.g., `ntl-11.4.3/src`
3. NTL is configured, built and installed in the standard Unix way (but remember to specify the following flags to `configure`):

```bash
./configure NTL_GMP_LIP=on SHARED=on NTL_THREADS=on NTL_THREADS_BOOST=on
make
sudo make install
```
This should install NTL into `/usr/local`.
**NOTE**: For futher options when building NTL, run `./configure --help` in step 3.
**NOTE**: if linking against a non-system GMP, pass `GMP_PREFIX=<path/to/gmp>` to the `./configure` step.

## Building CGSW
Within the CGSW root folder,
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

All the executable binary (target) will then be generated inside `build/bin`. To run any specific test cases,
do `./tests "CGSW1: Basic Addition"`, where `CGSW1: Basic Addition` is the test case of interest.




xamples of cmake-based projects whcih uses CGSW can be found in the `examples` directory.