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

    using record = std::tuple<uint64_t , uint64_t>;
    auto extent = GENERATE(table<uint64_t , uint64_t>({
                      record{8, 89},
                      record{16, 25523},
                      record{24, 7332551}}));
    uint64_t d = 3,
            k = std::get<0>(extent),
            n = k,
            q = std::get<1>(extent),
            l = ceil(log2(q)),
            m = l * n;

    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(3);
    parms.set_security_level(std::get<0>(extent));
    parms.set_modulus(std::get<1>(extent));
    CGSWContext context(parms);

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(context, public_key);
    Decryptor decryptor(context, secret_key);

    SECTION("Encrypt then decrypt"){

        WHEN("Encrypting 0"){
            Plaintext plain(context, 0);
            Ciphertext encrypted;
            encryptor.encrypt(plain, encrypted);

            Plaintext decrypted;
            decryptor.decrypt(encrypted, decrypted);

            REQUIRE(decrypted.data() == 0);
        }

        WHEN("Decrypting 1"){
            Plaintext plain(context, 1);
            Ciphertext encrypted;
            encryptor.encrypt(plain, encrypted);

            Plaintext decrypted;
            decryptor.decrypt(encrypted, decrypted);

            REQUIRE(decrypted.data() == 1);
        }
    }
}