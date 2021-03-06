//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include "ciphertext.hpp"
#include "encryptionparams.hpp"
#include "plaintext.hpp"
#include "publickey.hpp"
#include <iostream>

#include "cgsw/utils/utils.hpp"


namespace cgsw {

    typedef std::vector<std::vector<Ciphertext>> ddCipherMatrix;
    typedef std::vector<std::vector<std::vector<Ciphertext>>> dddCipherMatrix;

    class Encrypter {

        public:
            Encrypter(const EncryptionParameters &params, const PublicKey &public_key);

            // TODO:- can consolidate the two following into one single encrypt with diff signature ?
            void encrypt_gsw(const GSWPlaintext &plain, Ciphertext &destination);

            void encrypt_cgsw(const CGSWPlaintext &plains, dddCipherMatrix &destination);

            CGSWCiphertext compress(const dddCipherMatrix &ciphertexts);

            void encrypt_compress(const CGSWPlaintext &plains, CGSWCiphertext &destination);

            inline void set_public_key(const PublicKey &public_key)
            {
                public_key_ = public_key;
            }

    private:

            void smart_compress_cgsw1(const dddCipherMatrix &ciphertexts, CGSWCiphertext &results);

            void normal_compress_cgsw1(const dddCipherMatrix &ciphertexts, CGSWCiphertext &results);

            void normal_compress_cgsw2(const dddCipherMatrix &ciphertexts, CGSWCiphertext &results);

            void encrypt_mat(const CGSW_mat_uint &plain, ddCipherMatrix &destination);

            void encrypt_single_bit(const uint64_t &input, Ciphertext &destination);

            inline CGSW_mat generate_t_matrix(uint64_t scalar, int u, int v, size_t n1, size_t n0);

            inline CGSW_vec generate_t_vector(uint64_t scalar, uint64_t v, uint64_t l, uint64_t length);

            EncryptionParameters params_;

            CGSW_mat gadget_matrix_;

            PublicKey public_key_;
    };
}
