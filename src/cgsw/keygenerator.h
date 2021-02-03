//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include "encryptionparams.h"
#include <cstddef>
#include "common.h"
#include "utils/utils.h"
#include "secretkey.h"
#include "publickey.h"

using namespace Eigen;

namespace cgsw {

    /**
    Generates matching secret key and public key. Constructing a KeyGenerator requires only a CGSWContext.

    @see EncryptionParameters for more details on encryption parameters.
    @see SecretKey for more details on secret key.
    @see PublicKey for more details on public key.
    */
    class KeyGenerator {
        public:

            KeyGenerator() = default;
            /**
            Creates a KeyGenerator initialized with the specified SEALContext.

            @param[in] context The SEALContext
            @throws std::invalid_argument if the encryption parameters are not valid
            */
            KeyGenerator(const EncryptionParameters &params);

            /**
            Returns a const reference to the secret key.
            */
            const SecretKey &secret_key() const;

            /**
            Generates a public key and stores the result in destination. Every time
            this function is called, a new public key will be generated.

            @param[out] destination The public key to overwrite with the generated
            public key
            */
            inline void create_public_key(PublicKey &destination)
            {
                destination = generate_pk();
            }



    private:

            void generate_sk();

            PublicKey generate_pk();

            EncryptionParameters params_;

            dynMatrix gadget_matrix_;

            SecretKey secret_key_;

            bool sk_generated_ = false;
    };

}




