//
// Created by Chi Keen Tan on 16/01/2021.
//

#include "catch.hpp"
#include "../src/cgsw.h"

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

    SECTION("Addition"){
        WHEN("0 + 0"){
            THEN( "= 0") {

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