//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include "context.h"
#include "plaintext.h"
#include "ciphertext.h"
#include "secretkey.h"

#include "utils/matrixgenerator.h"

namespace cgsw {

    class Decryptor{

        public:
            Decryptor(const CGSWContext &context, const SecretKey &secret_key);

            void decrypt(const Ciphertext &encrypted, Plaintext &destination);

            int invariant_noise_budget(const Ciphertext &encrypted); // TODO:- somehow implement this

        private:
            CGSWContext context_;

            SecretKey secret_key_;

            dynMatrix gadget_matrix_;

    };
}