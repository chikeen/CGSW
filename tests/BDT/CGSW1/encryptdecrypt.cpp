//
// Created by Chi Keen Tan on 14/01/2021.
//

#include "../../catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;

TEST_CASE("EncryptCompressDecrypt CGSW tests"){
    auto k = GENERATE(2);
    auto rate = GENERATE(0.5);

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.set_rate(rate);
    params.compute();

    INFO("Params: " << params);

    KeyGenerator keygen(params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    Encryptor encryptor(params, public_key);
    Decryptor decryptor(params, secret_key);

    uint64_t n0 = params.getLatticeDimension0();

    // 1. Generate a random m matrix
    int p;
    conv(p, params.getPlainModulus());
    CGSW_mat_uint m;
    util::gen_random_uint_matrix(m, n0, n0, p);

    INFO("message matrix, m = " << m);

    // 2. initialize a CGSWPlaintext
    CGSWPlaintext plain(params, m);
    plain.generate_bit_decomposed_plaintexts();

    INFO("Example of decomposed plaintext : \n" << plain.bit_decomposed_data()[params.getPL() -1]);

    // Encrypting those plaintexts into ciphertexts
    dddCipherMatrix ciphertexts;
    encryptor.encrypt_cgsw(plain, ciphertexts);
    INFO("first ciphertext = \n" << ciphertexts[0][0][0].data());
    INFO("size of ciphertexts: " << ciphertexts.size() << ", " << ciphertexts[0].size()
                                 << ", " << ciphertexts[0][0].size());

    // "ciphertexts should have size l x (n x n)"
    REQUIRE(ciphertexts.size() == params.getPL());
    REQUIRE(ciphertexts[0].size() == params.getLatticeDimension0());
    REQUIRE(ciphertexts[0][0].size() == params.getLatticeDimension0());

    // 3. Compressing the ciphertexts
    Ciphertext c = encryptor.compress(ciphertexts);
    INFO("Compressed: \n" << c.data());


    // 4. Compressed decryptions
    CGSWPlaintext decrypted;
    decryptor.compressed_decrypt(c, decrypted);
    INFO("Decrypted message: \n" << decrypted.data());
    REQUIRE(1 == 2);

}
