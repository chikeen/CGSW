//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include "ciphertext.hpp"
#include "plaintext.hpp"
#include "secretkey.hpp"

#include "cgsw/utils/utils.hpp"
#include <utility>

namespace cgsw {

    class Decrypter{

        public:
            Decrypter(const EncryptionParameters &context, const SecretKey &secret_key);

            void decrypt_gsw(const Ciphertext &encrypted, GSWPlaintext &decrypted);

            void compressed_decrypt(const Ciphertext &encrypted, CGSWPlaintext &decrypted);

            int invariant_noise_budget(const Ciphertext &encrypted); // TODO:- somehow implement this

        private:

            void compressed_decrypt_cgsw1(const Ciphertext &encrypted, CGSWPlaintext &decrypted);

            void compressed_decrypt_cgsw2(const Ciphertext &encrypted, CGSWPlaintext &decrypted);

            EncryptionParameters params_;

            SecretKey   secret_key_;

            CGSW_mat gadget_matrix_;

    };
}