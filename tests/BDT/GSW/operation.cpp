//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "../../catch.hpp"
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;

TEST_CASE("GSW Addition tests"){

    auto k = GENERATE(8, 16);
    uint64_t d = 3;

    EncryptionParameters params(scheme_type::gsw);
    params.set_circuit_depth(d);
    params.set_security_level(k);
    params.compute();

    INFO("Params:" << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encrypter encryptor(params, public_key);
    Evaluator evaluator(params);
    Decrypter decryptor(params, secret_key);

    // ----- preparing data ----------
    GSWPlaintext plain_0(0), plain_1a(1), plain_1b(1);
    Ciphertext encrypted_0, encrypted_1a, encrypted_1b;
    encryptor.encrypt_gsw(plain_0, encrypted_0);
    encryptor.encrypt_gsw(plain_1a, encrypted_1a);
    encryptor.encrypt_gsw(plain_1b, encrypted_1b);

//    WHEN("Adding 0 to 0") {
//        Ciphertext encrypted_result;
//        evaluator.add(encrypted_0, encrypted_0, encrypted_result);
//
//        THEN(" = 0"){
//            GSWPlaintext result;
//            decryptor.decrypt_gsw(encrypted_result, result);
//            REQUIRE(result.data() == 0);
//        }
//    }
//
//    WHEN("Adding 0 to 1") {
//        Ciphertext encrypted_result;
//        evaluator.add(encrypted_0, encrypted_1a, encrypted_result);
//
//        THEN(" = 1"){
//            GSWPlaintext result;
//            decryptor.decrypt_gsw(encrypted_result, result);
//            REQUIRE(result.data() == 1);
//        }
//    }
//
//    WHEN("Adding 1 to 0") {
//        Ciphertext encrypted_result;
//        evaluator.add(encrypted_1a, encrypted_0, encrypted_result);
//
//        THEN(" = 1"){
//            GSWPlaintext result;
//            decryptor.decrypt_gsw(encrypted_result, result);
//            REQUIRE(result.data() == 1);
//        }
//    }
//
//    WHEN("Adding 1 to 1") {
//        Ciphertext encrypted_result;
//        evaluator.add(encrypted_1a, encrypted_1b, encrypted_result);
//
//        INFO("encrypted_1a" << encrypted_1a.data());
//        INFO("encrypted_1b" << encrypted_1b.data());
//        INFO("encrypted_result " << encrypted_result.data());
//
//        THEN(" = 2"){
//            GSWPlaintext result;
//            decryptor.decrypt_gsw(encrypted_result, result);
//            REQUIRE(result.data() == 2);
//        }
//    }

    WHEN("Subing 1 from 1") {
        Ciphertext encrypted_result;
        evaluator.sub(encrypted_1a, encrypted_1b, encrypted_result);
        INFO("encrypted_1a" << encrypted_1a.data());
        INFO("encrypted_1b" << encrypted_1b.data());
        INFO("encrypted_result " << encrypted_result.data());

        THEN(" = 0"){
            GSWPlaintext result;
            decryptor.decrypt_gsw(encrypted_result, result);
            REQUIRE(result.data() == 0);
        }
    }


}
