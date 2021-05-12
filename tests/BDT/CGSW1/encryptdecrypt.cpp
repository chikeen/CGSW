//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "../../catch.hpp"
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;

TEST_CASE("CGSW1: Basic encryptdecrypt test"){

    auto k = GENERATE(2);
    auto rate = GENERATE(0.2);

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    INFO("Params: " << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    INFO("Secret key: " << secret_key.sk());
    PublicKey public_key = keygen.create_public_key();

    Encrypter encryptor(params, public_key);
    Decrypter decryptor(params, secret_key);

    uint64_t n0 = params.getLatticeDimension0();

    // 1. Generate a random m matrix
    int p;
    conv(p, params.getPlainModulus());
    CGSW_mat_uint m;
    util::gen_random_uint_matrix(m, n0, n0, p/2);

    INFO("message matrix, m = \n" << m);

    // 2. initialize a CGSWPlaintext
    CGSWPlaintext plain(params, m);
    plain.generate_bit_decomposed_plaintexts();

//    INFO("Example of decomposed plaintext : \n" << plain.bit_decomposed_data()[params.getPL() -1]);

//    // Encrypting those plaintexts into ciphertexts
//    dddCipherMatrix ciphertexts;
//    encryptor.encrypt_cgsw(plain, ciphertexts);
////    INFO("first ciphertext = \n" << ciphertexts[0][0][0].data());
//    INFO("size of ciphertexts: " << ciphertexts.size() << ", " << ciphertexts[0].size()
//                                 << ", " << ciphertexts[0][0].size());
//
//    // "ciphertexts should have size l x (n x n)"
//    REQUIRE(ciphertexts.size() == params.getPL());
//    REQUIRE(ciphertexts[0].size() == params.getLatticeDimension0());
//    REQUIRE(ciphertexts[0][0].size() == params.getLatticeDimension0());

    // 3. Compressing the ciphertexts
    CGSWCiphertext c;
    encryptor.encrypt_compress(plain, c);
//    INFO("Compressed: \n" << c.data());


    // 4. Compressed decryptions
    CGSWPlaintext decrypted;
    decryptor.compressed_decrypt(c, decrypted);
    INFO("Decrypted message: \n" << decrypted.data());
    INFO("error in decrypting message:\n" << decrypted.data() - plain.data());
//    INFO("error in decrypting message / f\n" << (decrypted.data() - plain.data()) / params.getF());
    REQUIRE(1 == 2);

}

TEST_CASE("CGSW1: encrypt same plaintext give diff ciphertext"){

    auto k = GENERATE(2);
    auto rate = GENERATE(0.4);

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    INFO("Params: " << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    INFO("Secret key: " << secret_key.sk());
    PublicKey public_key = keygen.create_public_key();

    Encrypter encryptor(params, public_key);
    Decrypter decryptor(params, secret_key);

    uint64_t n0 = params.getLatticeDimension0();

    // 1. Generate a random m matrix
    int p;
    conv(p, params.getPlainModulus());
    CGSW_mat_uint m;
    util::gen_random_uint_matrix(m, n0, n0, p/2);

    INFO("message matrix, m = \n" << m);

    // 2. initialize a CGSWPlaintext
    CGSWPlaintext plain(params, m);
    plain.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c1, c2;
    encryptor.encrypt_compress(plain, c1);
    encryptor.encrypt_compress(plain, c2);
    INFO("Compressed 1: \n" << c1.data());
    INFO("Compressed 2: \n" << c2.data());


    // 4. Compressed decryptions
    CGSWPlaintext decrypted1, decrypted2;
    decryptor.compressed_decrypt(c1, decrypted1);
    INFO("Decrypted message 1: \n" << decrypted1.data());
    INFO("error in decrypting message:\n" << decrypted1.data() - plain.data());

    decryptor.compressed_decrypt(c2, decrypted2);
    INFO("Decrypted message2 : \n" << decrypted2.data());
    INFO("error in decrypting message:\n" << decrypted2.data() - plain.data());

    REQUIRE(1 == 2);
}


