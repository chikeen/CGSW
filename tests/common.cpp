//
// Created by Chi Keen Tan on 03/02/2021.
//

#include "catch.hpp"
#include "../src/cgsw/common.h"

using namespace std;


TEST_CASE("Test Eigen custom scalar type"){
    auto a = GENERATE(100, 100000, 124346345, 1343451346);

    SECTION("test log2"){
        matrixElemType zz(a);
        REQUIRE(ceil(log2(a)) == ceil(log2(zz)));
        REQUIRE(floor(log2(a)) == floor(log2(zz)));
    }

}