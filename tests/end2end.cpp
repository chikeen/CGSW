//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "catch.hpp"
#include "../src/cgsw/cgsw.h"

using namespace cgsw;
using namespace std;

/*
 * Cases (k, q):
 *  1. 8, 89
 *  2. 16, 25523
 *  3. 24, 7332551
 */

TEST_CASE("End to end tests"){

    auto k = GENERATE(8, 16);
    uint64_t d = 3;

    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(3);
    parms.set_security_level(k);

    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(parms, public_key);
    Decryptor decryptor(parms, secret_key);

    SECTION("Encrypt then decrypt"){

        WHEN("Encrypting 0"){
            Plaintext plain(0);
            Ciphertext encrypted;
            encryptor.encrypt(plain, encrypted);

            Plaintext decrypted;
            decryptor.decrypt(encrypted, decrypted);

            REQUIRE(decrypted.data() == 0);
        }

        WHEN("Decrypting 1"){
            Plaintext plain(1);
            Ciphertext encrypted;
            encryptor.encrypt(plain, encrypted);

            Plaintext decrypted;
            decryptor.decrypt(encrypted, decrypted);
            INFO("modulus,q = " << parms.getModulus() );
            REQUIRE(decrypted.data() == 1);
        }
    }
}