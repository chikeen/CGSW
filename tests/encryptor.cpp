//
// Created by Chi Keen Tan on 13/01/2021.
//

#include "catch.hpp"
#include "../src/cgsw/cgsw.h"

using namespace cgsw;
using namespace std;


TEST_CASE("Encryptor Tests"){
    auto k = GENERATE(8, 16);

    EncryptionParameters parms(scheme_type::cgsw);
    parms.set_circuit_depth(3);
    parms.set_security_level(k);

    uint64_t n = parms.getLatticeDimension();

    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(parms, public_key);

    SECTION("Test encrypt_many (1 to many"){
        SECTION("size of resulting vectors"){}


    }
}

