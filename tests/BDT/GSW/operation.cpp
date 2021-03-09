//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "../../catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;

TEST_CASE("GSW Addition tests"){

    auto k = GENERATE(8, 16);
    uint64_t d = 3;

    EncryptionParameters params(scheme_type::gsw);
    params.set_circuit_depth(d);
    params.set_security_level(k);

    INFO("Params:" << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encryptor encryptor(params, public_key);
    Evaluator evaluator(params);
    Decryptor decryptor(params, secret_key);

    // ----- preparing data ----------
    Plaintext plain_0(0), plain_1(1);
    Ciphertext encrypted_0, encrypted_1;
    encryptor.encrypt_gsw(plain_0, encrypted_0);
    encryptor.encrypt_gsw(plain_1, encrypted_1);

    WHEN("Adding 0 to 0") {
        Ciphertext encrypted_result;
        evaluator.add(encrypted_0, encrypted_0, encrypted_result);

        THEN(" = 0"){
            Plaintext result;
            decryptor.decrypt(encrypted_result, result);
            REQUIRE(result.data() == 0);
        }
    }

    WHEN("Adding 0 to 1") {
        Ciphertext encrypted_result;
        evaluator.add(encrypted_0, encrypted_1, encrypted_result);

        THEN(" = 1"){
            Plaintext result;
            decryptor.decrypt(encrypted_result, result);
            REQUIRE(result.data() == 1);
        }
    }

    WHEN("Adding 1 to 0") {
        Ciphertext encrypted_result;
        evaluator.add(encrypted_1, encrypted_0, encrypted_result);

        THEN(" = 1"){
            Plaintext result;
            decryptor.decrypt(encrypted_result, result);
            REQUIRE(result.data() == 1);
        }
    }

    WHEN("Adding 1 to 1") {
        Ciphertext encrypted_result;
        evaluator.add(encrypted_1, encrypted_1, encrypted_result);

        THEN(" = 2"){
            Plaintext result;
            decryptor.decrypt(encrypted_result, result);
            REQUIRE(result.data() == 2);
        }
    }
}
