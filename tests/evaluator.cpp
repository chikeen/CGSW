//
// Created by Chi Keen Tan on 16/01/2021.
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

TEST_CASE("Evaluator") {
    uint64_t d = 3, k = 8, n = k, q = 89, l = ceil(log2(q));
    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(d);
    parms.set_security_level(k);
    parms.set_modulus(q);
    CGSWContext context(parms);

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);
    Decryptor decryptor(context, secret_key);
    Evaluator evaluator(context);

    Plaintext plain_0(context, 0);
    Plaintext plain_1(context, 1);

    Ciphertext encrypted_0;
    encryptor.encrypt(plain_0, encrypted_0);

    Ciphertext encrypted_1;
    encryptor.encrypt(plain_1, encrypted_1);

    SECTION("Addition"){

        WHEN("0 + 0"){
            Ciphertext added;
            evaluator.add(encrypted_0, encrypted_0, added);

            REQUIRE(added.data().rows() == encrypted_0.data().rows());
            REQUIRE(added.data().cols() == encrypted_0.data().cols());

            THEN( "= 0") {
                Plaintext decrypted;
                decryptor.decrypt(added, decrypted);
                REQUIRE(decrypted.data() == plain_0.data());
            }
        }

        WHEN("1 + 0"){
            THEN( "= 1") {

            }
        }

        WHEN("0 + 1"){
            THEN( "= 1") {

            }
        }

        WHEN("1 + 1"){
            THEN( "= 0") {

            }
        }

    }

    SECTION("Multiplication"){
        WHEN("0 * 0"){
            THEN( "= 0") {

            }
        }

        WHEN("1 * 0"){
            THEN( "= 0") {

            }
        }

        WHEN("0 * 1"){
            THEN( "= 0") {

            }
        }

        WHEN("1 * 1"){
            THEN( "= 1") {

            }
        }

    }



}