//
// Created by Chi Keen Tan on 04/02/2021.
//

#include "catch.hpp"
#include "../src/cgsw/cgsw.h"

using namespace cgsw;
using namespace std;

TEST_CASE("Plaintext Tests"){
    auto p = GENERATE(3, 5, 8);

    EncryptionParameters params(scheme_type::cgsw);
    params.set_circuit_depth(3);
    params.set_security_level(8);
    params.set_plain_modulus((matrixElemType) p);

    SECTION("test generate_bit_decomposed_plaintexts: first bit"){
        uint64_t n = params.getLatticeDimension0();
        int p;
        NTL::conv(p, params.getPlainModulus());
        dynUintMatrix m = util::gen_random_uint_matrix(n, n, (uint64_t) p);
        INFO("message matrix, m = " << m);

        CGSWPlaintext plain(params, m);
        plain.generate_bit_decomposed_plaintexts();

        std::vector<dynUintMatrix> decomposed_plaintext = plain.bit_decomposed_data();
        INFO("bit decomposed [0]" << decomposed_plaintext[0]);
        REQUIRE(decomposed_plaintext[0] == util::modulo_matrix(m, 2));
    }
}