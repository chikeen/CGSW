//
// Created by Chi Keen Tan on 05/03/2021.
//

#include "../catch.hpp"
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;


TEST_CASE("Microtestbench GSW"){

    auto k = GENERATE(8);
    uint64_t d = 3;

    double t0, ta, tb, sec_t, pub_t, enc_t, eval_t, dec_t;
    t0  = NTL::GetTime();

        EncryptionParameters params(scheme_type::gsw);
        params.set_circuit_depth(d);
        params.set_security_level(k);

        INFO("Params:" << params);

    ta = NTL::GetTime();
        KeyGenerator keygen(params);
        SecretKey secret_key = keygen.secret_key();
    tb = NTL::GetTime();
    sec_t = tb - ta;

    ta = NTL::GetTime();
        PublicKey public_key = keygen.create_public_key();
    tb = NTL::GetTime();
    pub_t = tb - ta;

        INFO("Time: " << NTL::GetTime());
        INFO("WallTime: " << NTL::GetWallTime());

        INFO("secret_key" << secret_key.sk());
        INFO("public_key" << public_key.data());

        Encrypter encryptor(params, public_key);
        Decrypter decryptor(params, secret_key);
        Evaluator evaluator(params);

        GSWPlaintext plain_0(0), plain_1(1);
        Ciphertext encrypted_0, encrypted_1, encrypted_ans;

    ta = NTL::GetTime();
        encryptor.encrypt_gsw(plain_0, encrypted_0);
        encryptor.encrypt_gsw(plain_1, encrypted_1);
    tb = NTL::GetTime();
    enc_t = (tb - ta)/2;

    ta = NTL::GetTime();
        evaluator.add(encrypted_0, encrypted_1, encrypted_ans);
    tb = NTL::GetTime();
    eval_t = tb - ta;

        GSWPlaintext decrypted;

    ta = NTL::GetTime();
        decryptor.decrypt(encrypted_ans, decrypted);
    tb = NTL::GetTime();
    dec_t = tb - ta;


    SECTION("Print Time"){
        INFO("Time 0: " << t0);
        INFO("sec_t" << sec_t);
        INFO("pub_t" << pub_t);
        INFO("enc_t" << enc_t);
        INFO("eval_t" << eval_t);
        INFO("dec_t" << dec_t);

        REQUIRE( 1 ==2 );
    }

}
