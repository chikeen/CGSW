cmake_minimum_required(VERSION 3.17)
project(CGSW20)

set(CMAKE_CXX_STANDARD 14)


# CMake instructions to make the static lib

add_library(
        # library name
        CGSW20

        # library type
        STATIC

        # library include
        include/cgsw/cgsw.h

        # library util files
        src/cgsw/utils/numth.h
        src/cgsw/utils/numth.cpp

        # library files

        ## export
        src/cgsw/cgsw.h

        ## utils
        src/cgsw/utils/eigenmvn.h
        src/cgsw/utils/matrixgenerator.h
        src/cgsw/utils/matrixgenerator.cpp
        src/cgsw/utils/utils.h
        src/cgsw/utils/utils.cpp

        ## basic object
        src/cgsw/modulus.h
        src/cgsw/modulus.cpp
        src/cgsw/matrix.h
        src/cgsw/matrix.cpp
        src/cgsw/ciphertext.h
        src/cgsw/ciphertext.cpp
        src/cgsw/plaintext.h
        src/cgsw/plaintext.cpp
        src/cgsw/secretkey.h
        src/cgsw/publickey.h
        src/cgsw/encryptionparams.h
        src/cgsw/encryptionparams.cpp
        src/cgsw/context.h
        src/cgsw/context.cpp

        ## tools
        src/cgsw/keygenerator.h
        src/cgsw/keygenerator.cpp
        src/cgsw/encryptor.h
        src/cgsw/encryptor.cpp
        src/cgsw/decryptor.h
        src/cgsw/decryptor.cpp
        src/cgsw/evaluator.h
        src/cgsw/evaluator.cpp

        ## examples
        examples/1_gsw_basics.cpp
        examples/examples.h
        examples/examples.cpp

        ## tests
        tests/utils/utils.cpp
        tests/catch.hpp
        tests/utils.cpp)


target_include_directories(CGSW20 PUBLIC ../include)

# CMake instructions to test using the static lib

SET( APP_EXE example )
SET( TESTS_EXE tests)

ADD_EXECUTABLE( ${APP_EXE}
        examples/examples.cpp )

ADD_EXECUTABLE( ${TESTS_EXE}
        tests/utils.cpp
        tests/utils/utils.cpp)

TARGET_LINK_LIBRARIES( ${APP_EXE}
        CGSW20)

TARGET_LINK_LIBRARIES( ${TESTS_EXE}
        CGSW20)

