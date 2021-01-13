//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include "encryptionparams.h"
#include "context.h"
#include <cstddef>
#include "common.h"
#include "thirdparty/Eigen/dense"
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
            KeyGenerator(const CGSWContext &context);

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

            void generate_gadget_matrix();

            void generate_error_matrix();

            void generate_sk();

            PublicKey generate_pk();


            CGSWContext context_;

            util::MatrixGenerator matrix_gen_;

            Eigen::Matrix<uint64_t, Eigen::Dynamic, Eigen::Dynamic> gadget_matrix_;

            SecretKey secret_key_;

            size_t secret_key_array_size_ = 0;

//            util::Pointer<std::uint64_t> secret_key_array_;
//
//            mutable util::ReaderWriterLocker secret_key_array_locker_;

            bool sk_generated_ = false;



    };

}




