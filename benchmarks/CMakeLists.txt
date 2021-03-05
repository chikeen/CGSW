add_executable(testbench
        ../tests/catch.hpp
        1_GSW.cpp
        2_CGSW.cpp
        )


TARGET_LINK_LIBRARIES(testbench
        CGSW20)