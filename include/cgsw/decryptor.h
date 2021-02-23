//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include "plaintext.h"
#include "ciphertext.h"
#include "secretkey.h"

#include "utils/utils.h"
#include <utility>

namespace cgsw {

    class Decryptor{

        public:
            Decryptor(const EncryptionParameters &context, const SecretKey &secret_key);

            void decrypt(const Ciphertext &encrypted, Plaintext &decrypted);

            void compressed_decrypt(const Ciphertext &encrypted, CGSWPlaintext &decrypted);

            int invariant_noise_budget(const Ciphertext &encrypted); // TODO:- somehow implement this

        private:
            EncryptionParameters params_;

            SecretKey secret_key_;

            dynMatrix gadget_matrix_;

    };
}