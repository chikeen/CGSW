//
// Created by Chi Keen Tan on 13/01/2021.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/cgsw/keygenerator.h"

using namespace cgsw;
using namespace std;

/*
 * Cases (k, q):
 *  1. 8, 89
 *  2. 16, 25523
 *  3. 24, 7332551
 */

TEST_CASE("Key Generator"){
    uint64_t d = 3,  k = 8, n = k, q = 89, l = ceil(log2(q));
    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(d);
    parms.set_security_level(k);
    parms.set_modulus(q);
    CGSWContext context(parms);

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    SECTION("Secret_key size"){
        REQUIRE(secret_key.sk().rows() == 1);
//        REQUIRE(secret_key.sv().rows() == 1);
        REQUIRE(secret_key.sk().cols() == n);
//        REQUIRE(secret_key.sv().cols() == n-1);
    }

    SECTION("Public_key size"){
        REQUIRE(public_key.data().rows() == n);
        REQUIRE(public_key.data().cols() == n * l);
    }

    SECTION("Public_key * Secret_key must equal small errors"){
        dynMatrix product =  secret_key.sk() * public_key.data();
        util::modulo_matrix(product, q);
        REQUIRE(product.norm() < n * q/2); // average size less than q/2
    }

}
