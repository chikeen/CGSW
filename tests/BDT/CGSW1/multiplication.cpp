//
// Created by Chi Keen Tan on 12/05/2021.
//
//
// Created by Chi Keen Tan on 14/03/2021.
//
#include "../../catch.hpp"
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;

TEST_CASE("CGSW: Multiplication tests") {

    auto k = GENERATE(2);
    auto rate = GENERATE(0.2);

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
    CGSW_mat_uint m1;
    util::gen_random_uint_matrix(m1, n0, n0, p_int/2);

    INFO("message matrix, m1 = \n" << m1);

    CGSWPlaintext p1(params, m1);
    p1.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c1;
    encrypter.encrypt_compress(p1, c1);

    // ------ answer setup -----------
    CGSWCiphertext c_ans;
    CGSWPlaintext p_ans;

    WHEN("Multiply by 3"){
        GSWPlaintext p2(3);
        GSWCiphertext c2;
        encrypter.encrypt_gsw(p2, c2);

        evaluator.multiply_inplace_gsw(c1, c2);
        decrypter.compressed_decrypt(c1, p_ans);

        INFO("Multiply 3, ans = \n" << p_ans.data());
        INFO("Multiply 3, check_ans = \n" << (p1 * 3).data());
        INFO("error in decrypting message:\n" << p_ans.data() - (p1 * 3).data());
        REQUIRE(p_ans == p1 * 3);
    }

    WHEN("Multiply by 0"){
        GSWPlaintext p2(0);
        GSWCiphertext c2;
        encrypter.encrypt_gsw(p2, c2);

        evaluator.multiply_inplace_gsw(c1, c2);
        decrypter.compressed_decrypt(c1, p_ans);

        INFO("Multiply 0, ans = \n" << p_ans.data());
        INFO("Multiply 0, check_ans = \n" << (p1 * 0).data());
        INFO("error in decrypting message:\n" << p_ans.data() - (p1 * 0).data());
        REQUIRE(p_ans == p1 * 0);
    }

    WHEN("Multiply twice"){
        GSWPlaintext p2(3);
        GSWCiphertext c2;
        encrypter.encrypt_gsw(p2, c2);

        evaluator.multiply_inplace_gsw(c1, c2);
        evaluator.multiply_inplace_gsw(c1, c2);
        decrypter.compressed_decrypt(c1, p_ans);

        INFO("Multiply 3, ans = \n" << p_ans.data());
        INFO("Multiply 3, check_ans = \n" << (p1 * 9).data());
        INFO("error in decrypting message:\n" << p_ans.data() - (p1 * 9).data());
        REQUIRE(p_ans == p1 * 9);
    }
}

TEST_CASE("CGSW Multiplication with GSW Plaintext Tests") {

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
    util::gen_random_uint_matrix(m1, n0, n0, p_int/2);
    util::gen_random_uint_matrix(m2, n0, n0, p_int/2);

    INFO("message matrix, m1 = \n" << m1);

    CGSWPlaintext p1(params, m1), p2(params, m2);
    p1.generate_bit_decomposed_plaintexts();
    p2.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c1;
    encrypter.encrypt_compress(p1, c1);

    // ------ answer setup -----------
    CGSWCiphertext c_ans;
    CGSWPlaintext p_ans;

    // ---- multiplying -----------
    evaluator.multiply_inplace_plaintext(c1, p2);
    decrypter.compressed_decrypt(c1, p_ans);

    INFO("Multiplying, ans = \n" << p_ans.data());
    INFO("Multiplying, check_ans = \n" << (p1 * p2).data());
    REQUIRE(p_ans == p1 * p2);
}