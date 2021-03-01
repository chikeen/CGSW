//
// Created by Chi Keen Tan on 16/01/2021.
//

#include "catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;

/*
 * Cases (k, q):
 *  1. 8, 89
 *  2. 16, 25523
 *  3. 24, 7332551
 */

//TEST_CASE("GSW: Encryption Parameters Tests"){
//
//    using record = std::tuple<uint64_t , uint64_t>;
//    auto extent = GENERATE(table<uint64_t , uint64_t>({
//                      record{8, 89},
//                      record{16, 25523},
//                      record{24, 7332551}}));
//    uint64_t d = 3,
//             k = std::get<0>(extent),
//             n = k;
//    matrixElemType q = (matrixElemType) std::get<1>(extent);
//    uint64_t l = ceil(log2(q)),
//             m = l * n;
//    EncryptionParameters parms(scheme_type::gsw);
//
//    parms.set_circuit_depth(d);
//    parms.set_security_level(k);
//    parms.set_cipher_modulus(q);
//
//    SECTION("Test q"){
//        REQUIRE(parms.getCipherModulus() == q);
//    }
//
//    SECTION("Test n"){
//        REQUIRE(parms.getLatticeDimension0() == n);
//    }
//
//    SECTION("Test l"){
//        REQUIRE(parms.getL() == l);
//    }
//
//    SECTION("Test m"){
//        REQUIRE(parms.getM() == m);
//    }
//}


TEST_CASE("GSW: Encryption Params Test: Given security level"){

    auto k = GENERATE(4, 8, 16, 32, 64, 128, 256);

    SECTION("Generate correct prime"){
        EncryptionParameters parms(scheme_type::gsw);

        parms.set_circuit_depth(3);
        parms.set_security_level(k);
        cout << k << ": " << parms.getCipherModulus() << endl;
        REQUIRE(NTL::NumBits(parms.getCipherModulus()) == k);
    }

    SECTION("Generate correct l"){
        EncryptionParameters parms(scheme_type::gsw);

        parms.set_circuit_depth(3);
        parms.set_security_level(k);
        INFO("Modulus, q = " << parms.getCipherModulus());
        REQUIRE(parms.getL() == ceil(log2(parms.getCipherModulus())));
        REQUIRE(ceil(log2(parms.getCipherModulus())) == k);
    }
}


TEST_CASE("CGSW: EncryptionParameters tests"){
    auto k = GENERATE(4, 16, 64, 128, 256);
    auto p_bits = GENERATE(4, 8, 16, 32);
//    auto k = GENERATE(16);
//    auto p_bits = GENERATE(32);

    EncryptionParameters parms(scheme_type::cgsw);
    parms.set_circuit_depth(3);

    SECTION("compute_parms text"){

        SECTION("not set should give default values"){
            parms.set_rate(0.5);
        }

        parms.set_plaintext_space_in_bit(p_bits);
        parms.set_security_level(k);
        parms.set_rate(0.5);

        INFO("k" << k);
        INFO("p_bits" << p_bits);
        INFO("Parms: " << parms);

        REQUIRE(1 == 2);
    }
}