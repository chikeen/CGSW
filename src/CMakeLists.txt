# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${ModernCMakeExample_SOURCE_DIR}/include/modern/*.hpp")
set(HEADER_LIST "${CGSW20_SOURCE_DIR}/include/cgsw/cgsw.h")

# Make an automatic library - will be static or dynamic based on user setting
add_library(
        # library name
        CGSW20

        # library type
        STATIC

        # library include
        ${HEADER_LIST}

        ## utils
        cgsw/utils/numth.cpp
        cgsw/utils/matrix.cpp

        cgsw/plaintext.cpp
        cgsw/encryptionparams.cpp

        ## tools
        cgsw/keygenerator.cpp
        cgsw/encryptor.cpp
        cgsw/decryptor.cpp
        cgsw/evaluator.cpp
)

# We need this directory, and users of our library will need it too
target_include_directories(CGSW20 PUBLIC ../include)
target_include_directories(CGSW20 PUBLIC ${NTL_INCLUDE_PATHS})

# This depends on (header only) boost
target_link_libraries(CGSW20 PRIVATE
        ${NTL_LIBRARIES}
        Eigen3::Eigen)

# All users of this library will need at least C++11
target_compile_features(CGSW20 PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
#source_group(
#        TREE "${PROJECT_SOURCE_DIR}/include"
#        PREFIX "Header Files"
#        FILES ${HEADER_LIST})


