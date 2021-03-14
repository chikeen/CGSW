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
        REQUIRE(parms.getQL() == ceil(log2(parms.getCipherModulus())));
        REQUIRE(ceil(log2(parms.getCipherModulus())) == k);
    }
}


TEST_CASE("CGSW: EncryptionParameters tests"){
    auto k = GENERATE(4, 16, 64, 128, 256);
    auto p_bits = GENERATE(4, 8, 16, 32);
//    auto k = GENERATE(16);
//    auto p_bits = GENERATE(32);

    EncryptionParameters parms(scheme_type::cgsw1);
    parms.set_circuit_depth(3);

    SECTION("compute_parms text"){

        SECTION("not set should give default values"){
            parms.set_rate(0.5);
        }

//        parms.set_plaintext_space_in_bit(p_bits);
        parms.set_security_level(k);
        parms.set_rate(0.5);

        INFO("k" << k);
        INFO("p_bits" << p_bits);
        INFO("Parms: " << parms);
    }
}

TEST_CASE("CGSW: Test set_cgsw_modulus"){

    auto k = GENERATE(16);
    auto rate = GENERATE(0.5);
//    auto k = GENERATE(4, 16, 64, 128, 256);
//    auto rate = GENERATE(0.9, 0.8, 0.5, 0.4, 0.2);
    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    INFO("Params: " << params);
    auto theta_lower_bound = 0.5;
    auto theta_upper_bound = 2;
    auto theta = 1 - rate;


    SECTION("Test p for theta bound"){
        REQUIRE(params.getPlainModulus() > pow(k, theta_lower_bound / theta ));
        REQUIRE(params.getPlainModulus() < pow(k, theta_upper_bound / theta ));
    }

    SECTION("Test q for theta bound"){
        REQUIRE(params.getCipherModulus() > pow(k, theta_lower_bound / theta ));
        REQUIRE(params.getCipherModulus() < pow(k, theta_upper_bound / theta ));
    }

    SECTION("Test p and q relationship"){
        SECTION("Not equal"){
            REQUIRE_FALSE( params.getCipherModulus() == params.getPlainModulus());
        }

        SECTION("q > p"){
            REQUIRE( params.getCipherModulus() > params.getPlainModulus());
            REQUIRE( 1 == 2);
        }
    }
}


TEST_CASE("CGSW2: CGSW params calculator"){
    auto sec_level = GENERATE(2, 4, 16, 64, 128);
    auto rate = GENERATE(0.2, 0.5, 0.8);

    EncryptionParameters params(scheme_type::cgsw2);
    params.find_cgsw2_modulus(sec_level, rate);
}
