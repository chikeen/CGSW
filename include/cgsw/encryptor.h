//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include <iostream>
#include "encryptionparams.h"
#include "plaintext.h"
#include "ciphertext.h"
#include "publickey.h"

#include "utils/utils.h"


namespace cgsw {

    typedef std::vector<std::vector<Ciphertext>> ddCipherMatrix;
    typedef std::vector<std::vector<std::vector<Ciphertext>>> dddCipherMatrix;

    class Encryptor {

        public:
            Encryptor(const EncryptionParameters &params, const PublicKey &public_key);

            void encrypt_gsw(const Plaintext &plain, Ciphertext &destination);

            /*
             * Used for cgsw schemes
             * Takes in 1d vector of bit-decomposed matrices (all with binary entries),
             * , and output a 3D vector of ciphertexts
             */
            void encrypt_cgsw(const CGSWPlaintext &plains, dddCipherMatrix &destination);

            /*
             * Compress a vector of vector of ciphertexts into a single result ciphertext
             */
//            void compress(const dddCipherMatrix &ciphertexts, Ciphertext &results);

            Ciphertext compress(const dddCipherMatrix &ciphertexts);

            inline void set_public_key(const PublicKey &public_key)
            {
                public_key_ = public_key;
            }

    private:

            void smart_compress(const dddCipherMatrix &ciphertexts, Ciphertext &results);

            void normal_compress(const dddCipherMatrix &ciphertexts, Ciphertext &results);
            /*
             * Takes in one single matrix m (with binary entries only),
             * , and output 2D vector of ciphertexts
             */
            void encrypt_mat(const CGSW_mat_uint &plain, ddCipherMatrix &destination);

            void encrypt_single_bit(const uint64_t &input, Ciphertext &destination);

            inline CGSW_mat generate_t_matrix(uint64_t scalar, int u, int v, size_t n1, size_t n0);

            inline CGSW_vec generate_t_vector(uint64_t scalar, uint64_t v, uint64_t l, uint64_t length);

            EncryptionParameters params_;

            CGSW_mat gadget_matrix_;

            PublicKey public_key_;
    };
}
