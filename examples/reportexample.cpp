
#include <cgsw/cgsw.hpp>
#include <iostream>

using namespace std;
using namespace cgsw;

int main(){
    /*
    Set params and initialise CGSW parms
    */
    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(3); // circuit depth == multiplicative depth
    parms.set_security_level(2);
    parms.compute();

    /*
     * Generate keys
    */
    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    // Initialisation
    Encrypter encryptor(parms, public_key);
    Evaluator evaluator(parms);
    Decrypter decryptor(parms, secret_key);

    /*
    To get started, we create a plaintext containing the constant 6.
    */
    GSWPlaintext plain_0(0), plain_1(1);

    /*
    We then encrypt the plaintext, producing a ciphertext.
    */
    Ciphertext encrypted_0, encrypted_1;
    encryptor.encrypt_gsw(plain_0, encrypted_0);
    encryptor.encrypt_gsw(plain_1, encrypted_1);

    /*
     * Adding the ciphertext
     */
    Ciphertext encrypted_result;
    evaluator.add(encrypted_0, encrypted_0, encrypted_result);

    /*
    We decrypt the ciphertext and print the resulting plaintext in order to
    demonstrate correctness of the encryption.
    */
    GSWPlaintext decrypted;
    decryptor.decrypt(encrypted, decrypted);
    REQUIRE(decrypted.data() == 1);

    return 1;
}
