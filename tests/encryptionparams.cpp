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
             n = k;
    matrixElemType q = (matrixElemType) std::get<1>(extent);
    uint64_t l = ceil(log2(q)),
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


TEST_CASE("Encryption Params Test: Given security level"){

    auto k = GENERATE(4, 8, 16, 32, 64, 128, 256);

    SECTION("Generate correct prime"){
        EncryptionParameters parms(scheme_type::gsw);

        parms.set_circuit_depth(3);
        parms.set_security_level(k);
        cout << k << ": " << parms.getModulus() << endl;
        REQUIRE(NTL::NumBits(parms.getModulus()) == k);
    }

    SECTION("Generate correct l"){
        EncryptionParameters parms(scheme_type::gsw);

        parms.set_circuit_depth(3);
        parms.set_security_level(k);
        INFO("Modulus, q = " << parms.getModulus());
        REQUIRE(parms.getL() == ceil(log2(parms.getModulus())));
        REQUIRE(ceil(log2(parms.getModulus())) == k);
    }
}
