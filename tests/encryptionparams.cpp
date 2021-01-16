//
// Created by Chi Keen Tan on 16/01/2021.
//

#include "catch.hpp"
#include "../src/cgsw/encryptionparams.h"

using namespace cgsw;
using namespace std;

/*
 * Cases (k, q):
 *  1. 8, 89
 *  2. 16, 25523
 *  3. 24, 7332551
 */

TEST_CASE("Encryption Parameters Tests"){

    using record = std::tuple<uint64_t , uint64_t>;
    auto extent = GENERATE(table<uint64_t , uint64_t>({
                      record{8, 89},
                      record{16, 25523},
                      record{24, 7332551}}));
    uint64_t d = 3,
             k = std::get<0>(extent),
             n = k,
             q = std::get<1>(extent),
             l = ceil(log2(q)),
             m = l * n;
    EncryptionParameters parms(scheme_type::gsw);

    parms.set_circuit_depth(d);
    parms.set_security_level(k);
    parms.set_modulus(q);

    SECTION("Test q"){
        REQUIRE(parms.getModulus() == q);
    }

    SECTION("Test n"){
        REQUIRE(parms.getLatticeDimension() == n);
    }

    SECTION("Test l"){
        REQUIRE(parms.getL() == l);
    }

    SECTION("Test m"){
        REQUIRE(parms.getM() == m);
    }
}
