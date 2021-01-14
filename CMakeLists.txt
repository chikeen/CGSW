cmake_minimum_required(VERSION 3.17)
project(CGSW20)

set(CMAKE_CXX_STANDARD 14)

# third party libraries

find_package(Boost 1.50 REQUIRED COMPONENTS random)
message(STATUS "Boost version: ${Boost_VERSION}")

if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
endif()

if(NOT TARGET Boost::random)
        add_library(Boost::random IMPORTED INTERFACE)
        set_property(TARGET Boost::random PROPERTY
                INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
        set_property(TARGET Boost::random PROPERTY
                INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})
endif()


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

#        ## tests
#        tests/utils/utils.cpp
#        tests/catch.hpp
        )


target_include_directories(CGSW20 PUBLIC ${BOOST_INCLUDE_DIRS})


# CMake instructions to test using the static lib

SET( APP_EXE example )
SET( TESTS_EXE tests)

ADD_EXECUTABLE( ${APP_EXE}
        examples/examples.cpp )


TARGET_LINK_LIBRARIES( ${APP_EXE}
        CGSW20
        Boost::random
        ${BOOST_LIBRARIES})

# Link thirdparties libraries

# ---tests


ADD_EXECUTABLE( ${TESTS_EXE}
        tests/catch.hpp
        tests/keygenerator.cpp
        tests/encryptor.cpp
        tests/decryptor.cpp
        tests/utils/utils.cpp
        tests/end2end.cpp)


TARGET_LINK_LIBRARIES( ${TESTS_EXE}
        CGSW20
        Boost::random)