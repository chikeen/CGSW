//
// Created by Chi Keen Tan on 14/03/2021.
//
#include "../../catch.hpp"
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;

TEST_CASE("CGSW1: Basic Addition") {

    auto k = GENERATE(2);
    auto rate = GENERATE(0.2);

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    INFO("Params:" << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encrypter encrypter(params, public_key);
    Evaluator evaluator(params);
    Decrypter decrypter(params, secret_key);

    auto n0 = params.getLatticeDimension0();
    auto p = params.getPlainModulus();

    // ----- preparing required data ----------
    int p_int;
    conv(p_int, p);
    CGSW_mat_uint m1, m2, empty;
    util::gen_random_uint_matrix(m1, n0, n0, p_int/10);
    util::gen_random_uint_matrix(m2, n0, n0, p_int/10);
    empty.SetDims(n0, n0);

    INFO("message matrix, m1 = \n" << m1);
    INFO("message matrix, m2 = \n" << m2);

    CGSWPlaintext p1(params, m1), p2(params, m2), p3(params, empty);
    p1.generate_bit_decomposed_plaintexts();
    p2.generate_bit_decomposed_plaintexts();
    p3.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c1, c2, c3;
    encrypter.encrypt_compress(p1, c1);
    encrypter.encrypt_compress(p2, c2);
    encrypter.encrypt_compress(p3, c3);

    // ------ answer setup -----------
    CGSWCiphertext c_ans;
    CGSWPlaintext p_ans;

//    WHEN("A + B"){
//        evaluator.add_inplace(c1, c2);
//        decrypter.compressed_decrypt(c1, p_ans);
//
//        INFO("Addition, ans = \n" << p_ans.data());
//        INFO("Addition, check_ans = \n" << (p1 + p2).data());
//        INFO("error in decrypting message:\n" << p_ans.data() - (p1 + p2).data());
//        REQUIRE(p_ans == (p1 + p2));
//    }

//    WHEN("A + 0 = A"){
//        evaluator.add_inplace(c1, c3);
//        decrypter.compressed_decrypt(c1, p_ans);
//
//        INFO("Addition, ans = \n" << p_ans.data());
//        INFO("Addition, check_ans = \n" << p1.data());
//        INFO("error in decrypting message:\n" << p_ans.data() - (p1).data());
//        REQUIRE(p_ans == p1);
//    }

    WHEN("A - A = 0"){
        CGSWCiphertext c1b;
        encrypter.encrypt_compress(p1, c1b);

        evaluator.sub_inplace(c1, c1b);
        decrypter.compressed_decrypt(c1, p_ans);

        INFO("Addition, ans = \n" << p_ans.data());
        INFO("Addition, check_ans = \n" << (p3).data());
        INFO("error in decrypting message:\n" << p_ans.data() - (p3).data());
        REQUIRE(p_ans == (p3));
    }
}

TEST_CASE("CGSW1: Triple Addition Tests") {

    auto k = 2;
    auto rate = 0.2;

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    INFO("Params:" << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encrypter encrypter(params, public_key);
    Evaluator evaluator(params);
    Decrypter decrypter(params, secret_key);

    auto n0 = params.getLatticeDimension0();
    auto p = params.getPlainModulus();

    // ----- preparing data ----------
    int p_int;
    conv(p_int, p);
    CGSW_mat_uint m1, m2, m3;
    util::gen_random_uint_matrix(m1, n0, n0, p_int/10);
    util::gen_random_uint_matrix(m2, n0, n0, p_int/10);
    util::gen_random_uint_matrix(m3, n0, n0, p_int/10);

    INFO("message matrix, m1 = \n" << m1);
    INFO("message matrix, m2 = \n" << m2);
    INFO("message matrix, m2 = \n" << m3);

    CGSWPlaintext p1(params, m1), p2(params, m2), p3(params, m3);
    p1.generate_bit_decomposed_plaintexts();
    p2.generate_bit_decomposed_plaintexts();
    p3.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c1, c2, c3;
    encrypter.encrypt_compress(p1, c1);
    encrypter.encrypt_compress(p2, c2);
    encrypter.encrypt_compress(p3, c3);

    // ------ answer setup -----------
    CGSWCiphertext c_ans;
    CGSWPlaintext p_ans;

    WHEN("Normal Addition"){
        evaluator.add_inplace(c1, c2);
        evaluator.add_inplace(c1, c3);
        decrypter.compressed_decrypt(c1, p_ans);

        INFO("Addition, ans = \n" << p_ans.data());
        INFO("Addition, check_ans = \n" << (p1 + p2 + p3).data());
        INFO("error in decrypting message:\n" << p_ans.data() - (p1 + p2 + p3).data());
        REQUIRE(p_ans == (p1 + p2 + p3));
    }
}

TEST_CASE("General tests"){
    auto k = GENERATE(2);
    auto rate = GENERATE(0.5);

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    INFO("Params:" << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encrypter encrypter(params, public_key);
    Evaluator evaluator(params);
    Decrypter decrypter(params, secret_key);

    auto n0 = params.getLatticeDimension0();
    auto p = params.getPlainModulus();

    // ----- preparing data ----------
    int p_int;
    conv(p_int, p);
    CGSW_mat_uint m1, m2;
    m1.SetDims(n0, n0);
    INFO("empty matrix?: " << m1);

    REQUIRE(1 ==2);
}

