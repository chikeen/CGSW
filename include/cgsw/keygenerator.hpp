//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include "cgsw/utils/utils.hpp"
#include "common.hpp"
#include "encryptionparams.hpp"
#include "publickey.hpp"
#include "secretkey.hpp"
#include <cstddef>

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

            KeyGenerator(const EncryptionParameters &params);

            const SecretKey &secret_key() const;

            inline void create_public_key(PublicKey &destination){
                destination = generate_pk();
            }

            inline PublicKey create_public_key(){
                return generate_pk();
            }

    private:

            void generate_sk();

            PublicKey generate_pk();

            EncryptionParameters params_;

            SecretKey secret_key_;

            bool sk_generated_ = false;
    };

}




