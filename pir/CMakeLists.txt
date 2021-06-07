add_executable(pir
#        server/dbms.cpp
        server/server.hpp
        server/server.cpp
        client/client.hpp
        client/client.cpp
        )


TARGET_LINK_LIBRARIES(pir
        CGSW20)

add_executable(pir_examples
        server/server.hpp
        server/server.cpp
        client/client.hpp
        client/client.cpp
        examples/examples.cpp
        examples/examples.hpp
        examples/1_simplest_int.cpp
        examples/2_simplest_str.cpp
        examples/3_compressed_query.cpp
        )

TARGET_LINK_LIBRARIES(pir_examples
        CGSW20)