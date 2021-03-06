
#include "examples.hpp"

using namespace std;
using namespace cgsw;

void example_gsw_basics() {
    print_example_banner("Example: GSW Basics");


    /*
     * This is an example of a low-rate(uncompressed) FHE scheme), which are able to encrypt only 0, or 1
     */

    /*
    Set params and initialise CGSW parms
    */
    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(3); // circuit depth == multiplicative depth
    parms.set_security_level(8);

    print_line(__LINE__);
    cout << "Set encryption parameters and print" << endl;
    print_parameters(parms);

    cout << endl;
    cout << "~~~~~~ A naive way to calculate 4(x^2+1)(x+1)^2. ~~~~~~" << endl;


    /*
     * Generate keys
    */
    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

//    cout << "secret_key: " << endl << secret_key.sk() << endl;
//    cout << "public_key: " << endl << public_key.data() << endl;

    // Initialisation
    Encrypter encryptor(parms, public_key);
    Evaluator evaluator(parms);
    Decrypter decryptor(parms, secret_key);

    /*
    To get started, we create a plaintext containing the constant 6.
    */

    print_line(__LINE__);
    int x = 1, y = 9;
//    Plaintext x_plain(parms, x);
//    Plaintext y_plain(parms, y);
//    cout << "Express x = " + to_string(x) + " as a plaintext matrix" << x_plain.data() << "." << endl;

    /*
    We then encrypt the plaintext, producing a ciphertext.
    */
    print_line(__LINE__);
    Ciphertext x_encrypted;
    Ciphertext y_encrypted;
//    cout << "Encrypt x_plain to x_encrypted." << endl;
//    encryptor.encrypt(x_plain, x_encrypted);
//    encryptor.encrypt(y_plain, y_encrypted);

//    cout << "    + size of freshly encrypted x: " << x_encrypted.data().size() << endl;
//    cout << "Ciphertext: " << x_encrypted.data() << endl;
//    cout << "    + noise budget in freshly encrypted x: " << decryptor.invariant_noise_budget(x_encrypted) << " bits"
//         << endl;
//

    /*
    We decrypt the ciphertext and print the resulting plaintext in order to
    demonstrate correctness of the encryption.
    */

    GSWPlaintext x_decrypted;
    GSWPlaintext y_decrypted;
//    cout << "    + decryption of x_encrypted: ";
    decryptor.decrypt_gsw(x_encrypted, x_decrypted);
    decryptor.decrypt_gsw(y_encrypted, y_decrypted);
//    cout << "0x" << x_decrypted.data() << " ...... Correct." << endl;
}