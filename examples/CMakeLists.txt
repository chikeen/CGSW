add_executable(example
        examples.cpp
        1_gsw_basics.cpp)
target_compile_features(example PRIVATE cxx_std_17)

target_link_libraries(example PRIVATE CGSW20)
