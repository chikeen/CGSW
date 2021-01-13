//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include <iostream>
#include "context.h"
#include "plaintext.h"
#include "ciphertext.h"
#include "publickey.h"
#include "secretkey.h"

#include "utils/matrixgenerator.h"

namespace cgsw {

    class Encryptor {

        public:
            Encryptor(const CGSWContext &context, const PublicKey &public_key);

            void encrypt(Plaintext &plain, Ciphertext &destination);

            inline void set_public_key(const PublicKey &public_key)
            {
                public_key_ = public_key;
            }


    private:
            dynMatrix gadget_matrix_;

            CGSWContext context_;

            PublicKey public_key_;

            SecretKey secret_key_;
    };
}
