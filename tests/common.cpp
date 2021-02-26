//
// Created by Chi Keen Tan on 03/02/2021.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cgsw/cgsw.h>

using namespace std;


TEST_CASE("Test NTL custom Fucntion"){
    auto a = GENERATE(100, 100000, 124346345, 1343451346);

    SECTION("test log2"){
        CGSW_long zz(a);
        REQUIRE(ceil(log2(a)) == ceil(log2(zz)));
        REQUIRE(floor(log2(a)) == floor(log2(zz)));
    }

}