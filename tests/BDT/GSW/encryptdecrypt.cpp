//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "../../catch.hpp"
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;


TEST_CASE("EncryptDecrypt GSW tests"){

    auto k = GENERATE(3);

    EncryptionParameters params(scheme_type::gsw);
    params.set_security_level(k);
    params.compute();

    INFO("Params:" << params);
    cout << params << endl;

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    INFO("secret_key" << secret_key.sk());
    INFO("public_key" << public_key.data());

    Encrypter encryptor(params, public_key);
    Decrypter decryptor(params, secret_key);

    SECTION("simple GSW 1 bit"){

        WHEN("Encrypting 0"){
            GSWPlaintext plain(0);
            Ciphertext encrypted;
            encryptor.encrypt_gsw(plain, encrypted);

            GSWPlaintext decrypted;
            decryptor.decrypt_gsw(encrypted, decrypted);
            REQUIRE(decrypted.data() == 0);
        }

        WHEN("Encrypting 1"){
            GSWPlaintext plain(1);
            Ciphertext encrypted;
            encryptor.encrypt_gsw(plain, encrypted);

            GSWPlaintext decrypted;
            decryptor.decrypt_gsw(encrypted, decrypted);
            REQUIRE(decrypted.data() == 1);
        }

//        WHEN("Encrypting 2"){
//
        //            Plaintext plain(2);
//            Ciphertext encrypted;
//            encryptor.encrypt_gsw(plain, encrypted);
//
//            Plaintext decrypted;
//            decryptor.decrypt(encrypted, decrypted);
//            REQUIRE(decrypted.data() == 2);
//        }
    }
}
