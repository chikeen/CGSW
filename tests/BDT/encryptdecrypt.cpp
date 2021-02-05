//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "../catch.hpp"
#include "../../src/cgsw/cgsw.h"

using namespace cgsw;
using namespace std;

/*
 * Cases (k, q):
 *  1. 8, 89
 *  2. 16, 25523
 *  3. 24, 7332551
 */

TEST_CASE("EncryptDecrypt GSW tests"){

    auto k = GENERATE(8, 16);
    uint64_t d = 3;

    EncryptionParameters params(scheme_type::gsw);
    params.set_circuit_depth(d);
    params.set_security_level(k);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(params, public_key);
    Decryptor decryptor(params, secret_key);

    SECTION("simple GSW 1 bit"){

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
            INFO("modulus,q = " << params.getCipherModulus() );
            REQUIRE(decrypted.data() == 1);
        }
    }
}


TEST_CASE("EncryptCompressDecrypt CGSW tests"){
    auto k = GENERATE(3);

    EncryptionParameters params(scheme_type::cgsw);
    params.set_circuit_depth(3);
    params.set_security_level(k);

    uint64_t n = params.getLatticeDimension();

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(params, public_key);
    Decryptor decryptor(params, secret_key);

    WHEN("Encrypting m"){

        // 1. Generate a random m matrix
        int p;
        conv(p, params.getPlainModulus());
        dynUintMatrix m = util::gen_random_uint_matrix(n, n, (uint64_t) p);
        INFO("message matrix, m = " << m);

        THEN("message matrix, m should have entries less the p"){
            REQUIRE(m.maxCoeff() < p);
        }
        
        // 2. nitialize a CGSWPlaintext
        CGSWPlaintext plain(params, m);
        plain.generate_bit_decomposed_plaintexts();

        // Encrypting those plaintexts into ciphertexts
        dddCipherMatrix ciphertexts;
        encryptor.encrypt_many(plain.bit_decomposed_data(), ciphertexts);
        INFO("first ciphertext = " << ciphertexts[0][0][0].data());

        THEN("ciphertexts should have size l x (n x n)"){
//            REQUIRE(ciphertexts.size() == l);
//            REQUIRE(ciphertexts[0].size() == n);
        }

        // 3. Compressing the ciphertexts

        THEN("compressed ciphertext should be correct"){
            Ciphertext c = encryptor.compress(ciphertexts);
            INFO("Compressed: " << c.data());
            REQUIRE( 1== 2);
        }

    }

}