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
    auto k = 2;


    EncryptionParameters params(scheme_type::gsw);
    params.set_security_level(k);
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

    GSWPlaintext p3(0), p4(1);




    cout << "Time taken for Encryption: " << endl;
    start = high_resolution_clock::now();
    GSWCiphertext c3, c4;
    encrypter.encrypt_gsw(p3, c3);
    encrypter.encrypt_gsw(p4, c4);

    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() /2 << endl;


    cout << "Time taken for Addition: " << endl;
    start = high_resolution_clock::now();
    evaluator.add_inplace(c3, c4);
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

//    cout << "Time taken for Multiplication: " << endl;
//    start = high_resolution_clock::now();
//    evaluator.multiply_inplace(c3, c4);
//    stop = high_resolution_clock::now();
//    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    cout << "Time taken for Decryption: " << endl;
    start = high_resolution_clock::now();
    GSWPlaintext p_ans;
    decrypter.decrypt_gsw(c3, p_ans);
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    return 0;
}