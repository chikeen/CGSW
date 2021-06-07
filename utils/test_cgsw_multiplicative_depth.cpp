//
// Created by Chi Keen Tan on 24/04/2021.
//


#include <fstream>
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;


int main(){

    auto k = 2;
    auto rate = 0.2;

    // can reach multiplicative depth of 20

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    cout << params << endl;

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encrypter encrypter(params, public_key);
    Evaluator evaluator(params);
    Decrypter decrypter(params, secret_key);

    auto n0 = params.getLatticeDimension0();
    auto p = params.getPlainModulus();

    int p_int;
    conv(p_int, p);
    CGSW_mat_uint m1;
    util::gen_random_uint_matrix(m1, n0, n0, p_int/2);
    cout << "Data: " << m1 << endl;

    CGSWPlaintext p1(params, m1);
    p1.generate_bit_decomposed_plaintexts();

    CGSWCiphertext c1;
    encrypter.encrypt_compress(p1, c1);

    cout << "starting multiplication: " << endl;

    // ------ answer setup -----------
    CGSWCiphertext c_ans;
    CGSWPlaintext p_ans;

    for(int i = 0 ; i < 100; i ++){
        GSWPlaintext p2(1);
        GSWCiphertext c2;

        encrypter.encrypt_gsw(p2, c2);

        evaluator.multiply_inplace_gsw(c1, c2);
        decrypter.compressed_decrypt(c1, p_ans);

        if(p_ans.data() != m1){
            cout << p_ans.data() << endl;
            cout << "Differences: " << endl;
            cout << p_ans.data() - m1 << endl;
            cout << "Reached multiplicative depth: " << i << endl;
            break;
        }

        cout << "Multiplicative depth: " << i << " completed" << endl;
    }

    return 0;
}