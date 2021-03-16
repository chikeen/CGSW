//
// Created by Chi Keen Tan on 02/03/2021.
//
#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../tests/catch.hpp"
#include <cgsw/cgsw.h>


using namespace cgsw;
using namespace std;



TEST_CASE("BENCHMARKING GSW: "){
    auto k = GENERATE(8, 16);
    uint64_t d = 3;

    EncryptionParameters params(scheme_type::gsw);
    params.set_circuit_depth(d);
    params.set_security_level(k);

    INFO("Params:" << params);

    BENCHMARK("Secret key generation"){
        KeyGenerator keygen(params);
        return keygen.secret_key();
    };

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();

    BENCHMARK("Public key generation"){
        return keygen.create_public_key();
    };

    PublicKey public_key = keygen.create_public_key();

    Encrypter encryptor(params, public_key);
    Evaluator evaluator(params);
    Decrypter decryptor(params, secret_key);

    // ----- preparing data ----------
    GSWPlaintext plain_0(0);
    Ciphertext encrypted_0;

    BENCHMARK("Encryption"){
        return encryptor.encrypt(plain_0, encrypted_0);
    };

    encryptor.encrypt(plain_0, encrypted_0);

    GSWPlaintext decrypted_0;
    BENCHMARK("Decryption"){
       return decryptor.decrypt(encrypted_0, decrypted_0);;
    };

}