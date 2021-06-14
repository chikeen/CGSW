//
// Created by Chi Keen Tan on 05/03/2021.
//

#include <chrono>
#include <iostream>
#include <sstream>
#include <cgsw/cgsw.hpp>


using namespace std;
using namespace cgsw;
using namespace std::chrono;

int main(){
    auto rate = 0.2;
    auto k = 2;


    EncryptionParameters params(scheme_type::cgsw1);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    cout << params << endl;


    cout << "Time taken for SecretKey Generation: " << endl;
    auto start = high_resolution_clock::now();
    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    auto stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    cout << "Time taken for PublicKey Generation: " << endl;
    start = high_resolution_clock::now();
    PublicKey public_key = keygen.create_public_key();
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;



    Encrypter encrypter(params, public_key);
    Evaluator evaluator(params);
    Decrypter decrypter(params, secret_key);

    auto n0 = params.getLatticeDimension0();
    auto p = params.getPlainModulus();

    // ----- preparing data ----------
    int p_int;
    conv(p_int, p);
    CGSW_mat_uint m1, m2;
    util::gen_random_uint_matrix(m1, n0, n0, p_int/6);
    util::gen_random_uint_matrix(m2, n0, n0, p_int/6);

    GSWPlaintext p3(3);
    GSWCiphertext c3;
    encrypter.encrypt_gsw(p3, c3);


    cout << "Time taken for Compressed Encryption: " << endl;
    start = high_resolution_clock::now();
    CGSWPlaintext p1(params, m1);
    p1.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c1;
    encrypter.encrypt_compress(p1, c1);

    CGSWPlaintext p2(params, m2);
    p2.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c2;
    encrypter.encrypt_compress(p2, c2);

    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() /2 << endl;


    cout << "Time taken for Addition: " << endl;
    start = high_resolution_clock::now();
    evaluator.add_inplace(c1, c2);
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    cout << "Time taken for Multiplication: " << endl;
    start = high_resolution_clock::now();
    evaluator.multiply_inplace_gsw(c1, c3);
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    cout << "Time taken for Decryption: " << endl;
    start = high_resolution_clock::now();
    CGSWPlaintext p_ans;
    decrypter.compressed_decrypt(c1, p_ans);
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    return 0;
}