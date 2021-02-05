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

    class Encryptor {

        public:
            Encryptor(const EncryptionParameters &params, const PublicKey &public_key);

            void encrypt(const Plaintext &plain, Ciphertext &destination);

            /*
             * Takes in one single matrix m (with binary entries only),
             * , and output a vector of ciphertexts
             */
            void encrypt_many(const dynUintMatrix &plains, std::vector<Ciphertext> &destination);

            /*
             * Takes in a vector of bit-decomposed matrices (all with binary entries),
             * , and output a vector of vector of ciphertexts
             */
            void encrypt_many(const std::vector<dynUintMatrix> &plains, std::vector<std::vector<Ciphertext>> &destination);

            /*
             * Compress a vector of ciphertexts into a single result ciphertext
             */
            void compress(const std::vector<Ciphertext> &ciphertexts, Ciphertext &results);

            inline void set_public_key(const PublicKey &public_key)
            {
                public_key_ = public_key;
            }


    private:
            dynUintMatrix construct_T_prime_matrix();

            EncryptionParameters params_;

            dynMatrix gadget_matrix_;

            PublicKey public_key_;
    };
}
