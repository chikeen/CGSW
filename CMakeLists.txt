cmake_minimum_required(VERSION 3.17)

project(CGSW20
        VERSION 0.1
        DESCRIPTION "An Implementation of Compressible FHE")

# Fail if the target architecture is not 64-bit.
if (NOT (CMAKE_SIZEOF_VOID_P EQUAL 8))
        message(FATAL_ERROR "HElib requires a 64-bit architecture.")
endif ()

# Use -std=c++17 as default.
set(CMAKE_CXX_STANDARD 17)
# Disable C++ extensions
set(CMAKE_CXX_EXTENSIONS OFF)
# Require full C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ------ Folder Definitions ----------

# Define standard installation directories (GNU)
include(GNUInstallDirs)

# Setting compiler output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Location of the root folder of HElib (the one where this file is)
set(CGSW_PROJECT_ROOT_DIR "${PROJECT_SOURCE_DIR}")
# Location of the cmake extra files
set(CGSW_CMAKE_EXTRA_DIR "${PROJECT_SOURCE_DIR}/cmake")
# Prefix of the header files (directory to be added to the include list)
set(CGSW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
# Location of helib header files
set(CGSW_HEADER_DIR "${CGSW_INCLUDE_DIR}/helib")
# Location of the source files
set(CGSW_SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
# Location of the google tests
set(CGSW_TESTS_DIR "${PROJECT_SOURCE_DIR}/tests")
# Location of the dependencies
set(CGSW_DEPENDENCIES_DIR "${PROJECT_SOURCE_DIR}/dependencies")
# Location of the directory containing the test binary (runTests). If
# PACKAGE_BUILD=ON, this location will be changed to reflect the tests location.
set(CGSW_TEST_BIN_DIR "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")

# GMP minimal version to be used if not PACKAGE_BUILD
set(GMP_MINIMAL_VERSION "6.0.0")
# NTL minimal version to be used if NOT PACKAGE_BUILD
set(NTL_MINIMAL_VERSION "11.0.0")

# The -isysroot flag needs set.
if ((APPLE OR (CMAKE_CXX_PLATFORM_ID STREQUAL "Darwin")) AND
        # This addresses the problem when CMAKE_OSX_SYSROOT is "" (e.g. when /usr/include/sys/types.h exists)
        NOT CMAKE_OSX_SYSROOT STREQUAL "")
        set(macos_isysroot_flag "-isysroot ${CMAKE_OSX_SYSROOT}")
else()
        set(macos_isysroot_flag "")
endif()

## Setting up RelWithDebInfo as default CMAKE_BUILD_TYPE
if (NOT CMAKE_BUILD_TYPE)
        # Setting RelWithDebInfo as it will compile with -O2 -g
        set(CMAKE_BUILD_TYPE RelWithDebInfo
                CACHE
                STRING "Choose the type of build, options are: Debug RelWithDebInfo Release MinSizeRel"
                FORCE)
endif (NOT CMAKE_BUILD_TYPE)

# Creating and documenting TARGET_ARCHITECTURE cmake property
set(TARGET_ARCHITECTURE "${TARGET_ARCHITECTURE}"
CACHE
        STRING "Target architecture used for -march (default is native)")
# If TARGET_ARCHITECTURE is not set use default
if (NOT TARGET_ARCHITECTURE)
set(TARGET_ARCHITECTURE "native"
CACHE
        STRING "Target architecture used for -march (default is native)"
FORCE)
endif (NOT TARGET_ARCHITECTURE)

# Path containing FindGMP.cmake and FindNTL.cmake
list(APPEND CMAKE_MODULE_PATH "${CGSW_CMAKE_EXTRA_DIR}")
option(BUILD_SHARED "Build as shared library" OFF)

option(PACKAGE_BUILD
        "Download dependencies and build as a self-contained package"
        OFF)

find_package(GMP "${GMP_MINIMAL_VERSION}" REQUIRED)
find_package(NTL "${NTL_MINIMAL_VERSION}" REQUIRED)


find_package(Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})


# The compiled library code is here
add_subdirectory(src)

# The executable code is here
add_subdirectory(examples)

# The tests are here
add_subdirectory(tests)

# The testbench(benchmarks) are here
add_subdirectory(benchmarks)

# The utils are here
add_subdirectory(utils)

# The pir application are here
add_subdirectory(pir)

