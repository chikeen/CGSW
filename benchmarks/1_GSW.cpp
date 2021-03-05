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

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encryptor encryptor(params, public_key);
    Evaluator evaluator(params);
    Decryptor decryptor(params, secret_key);

    // ----- preparing data ----------
    Plaintext plain_0(0), plain_1(1);
    Ciphertext encrypted_0, encrypted_1;
    encryptor.encrypt(plain_0, encrypted_0);
    encryptor.encrypt(plain_1, encrypted_1);
    BENCHMARK("EncryptionParams generation"){

    }

    BENCHMARK("Secret key generation"){

    }

    BENCHMARK("Public key generation"){

    }
}