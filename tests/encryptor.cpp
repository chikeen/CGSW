//
// Created by Chi Keen Tan on 13/01/2021.
//

#include "catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;


TEST_CASE("Encryptor Tests"){
    auto k = GENERATE(8, 16);

    EncryptionParameters parms(scheme_type::cgsw);
    parms.set_circuit_depth(3);
    parms.set_security_level(k);

    uint64_t n = parms.getLatticeDimension0();

    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(parms, public_key);

    SECTION("Test encrypt_many (1 to many"){
        SECTION("size of resulting vectors"){
        }
    }
}

TEST_CASE("Test compress"){
    auto k = GENERATE(2);

    EncryptionParameters parms(scheme_type::cgsw);
    parms.set_circuit_depth(3);
    parms.set_security_level(k);

    uint64_t n = parms.getLatticeDimension0();

    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(parms, public_key);

    // Generating test data
    dynMatrix m(4, 4);
    m << ZZ(1), ZZ(1), ZZ(1), ZZ(1),
         ZZ(1), ZZ(1), ZZ(1), ZZ(1),
         ZZ(1), ZZ(1), ZZ(1), ZZ(1),
         ZZ(1), ZZ(1), ZZ(1), ZZ(1);

    Ciphertext c, result;
    c.set_data(m);

    std::vector<Ciphertext> v1{c};
    ddCipherMatrix v2{v1};
    dddCipherMatrix v3{v2};


    // Compress
    result = encryptor.compress(v3);

    SECTION("Correctly compressing a single matrix"){
        INFO("p" << parms.getPlainModulus());
        INFO("q: " << parms.getCipherModulus());
        INFO("result= " << result.data());
        REQUIRE (1 == 2);
    }
}


