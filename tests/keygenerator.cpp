//
// Created by Chi Keen Tan on 13/01/2021.
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

TEST_CASE("GSW: Key Generator"){

    auto k = GENERATE(4, 16, 128);

    EncryptionParameters params(scheme_type::gsw);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    INFO("params: " << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    auto n0 = params.getLatticeDimension0();
    auto n1 = params.getLatticeDimension1();
    auto m = params.getM();
    auto q = params.getCipherModulus();

    SECTION("Secret_key size"){
        REQUIRE(secret_key.sk().NumRows() == 1);
//        REQUIRE(secret_key.sv().NumRows() == 1);
        REQUIRE(secret_key.sk().NumCols() == n1);
//        REQUIRE(secret_key.sv().NumCols() == n0);
    }

    SECTION("Public_key size"){
        INFO("Modulus, q" << q);
        INFO("Modulus2, q " << params.getCipherModulus());

        REQUIRE(public_key.data().NumRows() == n1);
        REQUIRE(public_key.data().NumCols() == m);
    }

    SECTION("Public_key * Secret_key must equal small errors"){

        INFO("q: " << q );
        CGSW_mat product =  secret_key.sk() * public_key.data();
        INFO("product: " << product );
        REQUIRE(util::get_sum(product) < n1 * q/2); // average size less than q/2
    }
}

TEST_CASE("CGSW: Key Generator"){
    auto k = GENERATE(16);
    auto p_bits = 16;

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(k);
//    params.set_plaintext_space_in_bit(p_bits);
    params.set_rate(0.8);
    params.compute();

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    auto m = params.getM();
    auto q = params.getCipherModulus();
    auto n1 = params.getLatticeDimension1();
    auto n0 = params.getLatticeDimension0();
    INFO("params" << params);

    SECTION("Secret_key size"){
        REQUIRE(secret_key.sk().NumRows() == n0);
//        REQUIRE(secret_key.sv().NumRows() == n0);
        REQUIRE(secret_key.sk().NumCols() == n1);
//        REQUIRE(secret_key.sv().NumCols() == n1);
    }

    SECTION("Public_key size"){
        REQUIRE(public_key.data().NumRows() == n1);
        REQUIRE(public_key.data().NumCols() == m);
    }

    SECTION("Public_key * Secret_key must equal small errors"){
        CGSW_mat product =  secret_key.sk() * public_key.data();
        INFO("product: " << product );
        REQUIRE( 1 == 2);
//        REQUIRE(product.norm() < n0 * q/2); // average size less than q/2
    }
}
