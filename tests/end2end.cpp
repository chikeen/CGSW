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

std::vector<std::pair<int, int>> cases = {{8, 89}};


TEST_CASE("End to end test"){

    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(3);
    parms.set_security_level(8);
    parms.set_modulus(89);
    CGSWContext context(parms);

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);
    Decryptor decryptor(context, secret_key);

    cout << "secret_key:" << endl << secret_key.sk() << endl;
    cout << "public_key:" << endl << public_key.data() << endl;




    SECTION("Encrypt then decrypt"){

        WHEN("Encrypting 0"){
            Plaintext plain(context, 1);
            Ciphertext encrypted;
            encryptor.encrypt(plain, encrypted);

            Plaintext decrypted;
            decryptor.decrypt(encrypted, decrypted);

//            REQUIRE(plain.data() == decrypted.data());

            Plaintext plain2(context, 1);
            Ciphertext encrypted2;
            encryptor.encrypt(plain2, encrypted2);

            Plaintext decrypted2;
            decryptor.decrypt(encrypted2, decrypted2);

            REQUIRE(plain2.data() == decrypted2.data());
        }

        WHEN("Decrypting 1"){

        }

    }
}