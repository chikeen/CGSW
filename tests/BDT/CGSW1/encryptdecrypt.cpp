//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "../../catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;

TEST_CASE("EncryptCompressDecrypt CGSW tests"){
    auto k = GENERATE(4);
    auto p_bits = GENERATE(4);

    EncryptionParameters params(scheme_type::cgsw);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.set_plaintext_space_in_bit(p_bits);
    params.set_rate(0.5);

    INFO("Params: " << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(params, public_key);
    Decryptor decryptor(params, secret_key);

    uint64_t n0 = params.getLatticeDimension0();

    WHEN("Encrypting m"){

        // 1. Generate a random m matrix
        int p;
        conv(p, params.getPlainModulus());
        dynUintMatrix m = util::gen_random_uint_matrix(n0, n0, (uint64_t) p);
        INFO("message matrix, m = " << m);

        THEN("message matrix, m should have entries less the p"){
            REQUIRE(m.maxCoeff() < p);
        }
        
        // 2. initialize a CGSWPlaintext
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
        Ciphertext c = encryptor.compress(ciphertexts);
        INFO("Compressed: " << c.data());

        THEN("compressed ciphertext should be correct"){
//            REQUIRE( 1== 2);
        }

        // 4. Compressed decryptions
        CGSWPlaintext decrypted;
        decryptor.compressed_decrypt(c, decrypted);
        INFO("Decrypted message: " << decrypted.data());
        THEN("decrypted message should match orginal"){
            REQUIRE(1 == 2);
        }
    }

}