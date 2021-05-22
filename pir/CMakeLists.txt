add_executable(pir
        server/dbms.cpp
        )


TARGET_LINK_LIBRARIES(pir
        CGSW20)

add_executable(pir_examples
        examples/examples.cpp
        examples/examples.hpp
        examples/1_simplest_int.cpp
        examples/2_simplest_str.cpp
        )

TARGET_LINK_LIBRARIES(pir_examples
        CGSW20)