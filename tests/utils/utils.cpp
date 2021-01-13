//
// Created by Chi Keen Tan on 13/01/2021.
//

#include "../catch.hpp"
//#include "../../src/cgsw/cgsw.h"
#include "../../src/cgsw/utils/utils.h"

using namespace cgsw::util;

TEST_CASE("test G then G-1", "[Utils]"){
    uint64_t row = 24, col = 24;
    uint64_t modulus = 17;
    uint64_t l = ceil(log2(17));
    // Generate a random matrix
    dynMatrix random = gen_random_matrix(row, col, modulus);

    // G
    dynMatrix g = gen_gadget_matrix(row, col*l);

    // C = G . G-1(C)
    dynMatrix g_inverse_random = bit_decompose_matrix(random, l);
    dynMatrix random_p = g * g_inverse_random;
    modulo_matrix(random_p, modulus);

    REQUIRE(random.cols() == random_p.cols());
    REQUIRE(random.rows() == random_p.rows());
    REQUIRE(random == random_p);
}