add_executable(params_table
        gen_params_table.cpp
        )

add_executable(multiplicative_depth
        test_cgsw_multiplicative_depth.cpp
        )


TARGET_LINK_LIBRARIES(params_table
        CGSW20)


TARGET_LINK_LIBRARIES(multiplicative_depth
        CGSW20)