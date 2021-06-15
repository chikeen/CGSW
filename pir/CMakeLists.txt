

add_executable(pir_examples
        server/server.hpp
        server/server.cpp
        client/client.hpp
        client/client.cpp
        examples/examples.cpp
        examples/examples.hpp
        examples/1_simplest_str.cpp
        examples/2_compressed_query.cpp
        )

TARGET_LINK_LIBRARIES(pir_examples
        CGSW20)