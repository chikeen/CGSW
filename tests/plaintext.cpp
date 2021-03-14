//
// Created by Chi Keen Tan on 04/02/2021.
//

#include "catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;

TEST_CASE("Plaintext Tests"){
    auto p = GENERATE(3, 5, 8);

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(8);
    params.set_plain_modulus((CGSW_long) p );
    size_t n = params.getLatticeDimension0();

    SECTION("test generate_bit_decomposed_plaintexts: first bit"){
        int p;
        NTL::conv(p, params.getPlainModulus());
        CGSW_mat_uint m;
        util::gen_random_uint_matrix(m, n, n, p);
        INFO("message matrix, m = " << m);

        CGSWPlaintext plain(params, m);
        plain.generate_bit_decomposed_plaintexts();

        std::vector<CGSW_mat_uint> decomposed_plaintext = plain.bit_decomposed_data();
        INFO("bit decomposed [0]" << decomposed_plaintext[0]);
//        REQUIRE(decomposed_plaintext[0] == util::modulo_matrix(m, 2));
    }
}