//
// Created by Chi Keen Tan on 24/04/2021.
//



#include "examples.hpp"

using namespace std;
using namespace cgsw;

void example_gsw_basics() {
    print_example_banner("Example: CGSW Basics");

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    // In CGSW, security_level and rate dictate
//        - multiplicative depth
//        - plaintext slots
//        - matrix dimensions
//        - modulus size

    print_line(__LINE__);
    cout << "Set encryption parameters and print" << endl;
    print_parameters(parms);

    cout << endl;
    cout << "~~~~~~ A naive way to calculate c3 = c0*c1 + c2*1.5 ~~~~~~" << endl;

    /*
     * Generate keys
    */
    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    // Initialisation
    Encrypter encryptor(parms, public_key);
    Evaluator evaluator(parms);
    Decrypter decryptor(parms, secret_key);

    print_line(__LINE__);
    int x = 1, y = 9;

    print_line(__LINE__);
    Ciphertext x_encrypted;
    Ciphertext y_encrypted;


    GSWPlaintext x_decrypted;
    GSWPlaintext y_decrypted;

    decryptor.decrypt(x_encrypted, x_decrypted);
    decryptor.decrypt(y_encrypted, y_decrypted);
}
