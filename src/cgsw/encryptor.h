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

            void encrypt(Plaintext &plain, Ciphertext &destination);

            inline void set_public_key(const PublicKey &public_key)
            {
                public_key_ = public_key;
            }


    private:
            EncryptionParameters params_;

            dynMatrix gadget_matrix_;

            PublicKey public_key_;
    };
}
