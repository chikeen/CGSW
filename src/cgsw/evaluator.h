//
// Created by Chi Keen Tan on 17/12/2020.
//
#pragma once

#include "thirdparty/Eigen/dense"
#include "encryptionparams.h"
#include "ciphertext.h"

namespace cgsw {

    class Evaluator{

    public:
        /**
        Creates an Evaluator instance initialized with the specified CGSWContext.

        @param[in] context The CGSWContext
        @throws std::invalid_argument if the encryption parameters are not valid
        */
        Evaluator(const CGSWContext &context);

        /**
        Negates a ciphertext.

        @param[in] encrypted The ciphertext to negate
        @throws std::invalid_argument if encrypted is not valid for the encryption
        parameters
        */
        void negate_inplace(Ciphertext &encrypted);

        /**
        Negates a ciphertext and stores the result in the destination parameter.

        @param[in] encrypted The ciphertext to negate
        @param[out] destination The ciphertext to overwrite with the negated result
        @throws std::invalid_argument if encrypted is not valid for the encryption parameters
        @throws std::logic_error if result ciphertext is transparent
        */
        inline void negate(const Ciphertext &encrypted, Ciphertext &destination)
        {
            destination = encrypted;
            negate_inplace(destination);
        }

        /**
        Adds two ciphertexts. This function adds together encrypted1 and encrypted2 and stores the result in encrypted1.

        @param[in] encrypted1 The first ciphertext to add
        @param[in] encrypted2 The second ciphertext to add
        @throws std::invalid_argument if encrypted1 or encrypted2 is not valid for the encryption parameters
        @throws std::invalid_argument if encrypted1 and encrypted2 are in different NTT forms
        @throws std::invalid_argument if encrypted1 and encrypted2 are at different level or scale
        @throws std::logic_error if result ciphertext is transparent
        */
        void add_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);

        /**
        Adds two ciphertexts. This function adds together encrypted1 and encrypted2 and stores the result in the
        destination parameter.

        @param[in] encrypted1 The first ciphertext to add
        @param[in] encrypted2 The second ciphertext to add
        @param[out] destination The ciphertext to overwrite with the addition result
        @throws std::invalid_argument if encrypted1 or encrypted2 is not valid for the encryption parameters
        @throws std::invalid_argument if encrypted1 and encrypted2 are in different NTT forms
        @throws std::invalid_argument if encrypted1 and encrypted2 are at different level or scale
        @throws std::logic_error if result ciphertext is transparent
        */
        inline void add(const Ciphertext &encrypted1, const Ciphertext &encrypted2, Ciphertext &destination)
        {
            if (&encrypted2 == &destination)
            {
                add_inplace(destination, encrypted1);
            }
            else
            {
                destination = encrypted1;
                add_inplace(destination, encrypted2);
            }
        }

        /**
        Adds together a vector of ciphertexts and stores the result in the destination parameter.

        @param[in] encrypteds The ciphertexts to add
        @param[out] destination The ciphertext to overwrite with the addition result
        @throws std::invalid_argument if encrypteds is empty
        @throws std::invalid_argument if encrypteds are not valid for the encryption
        parameters
        @throws std::invalid_argument if encrypteds are in different NTT forms
        @throws std::invalid_argument if encrypteds are at different level or scale
        @throws std::invalid_argument if destination is one of encrypteds
        @throws std::logic_error if result ciphertext is transparent
        */
        void add_many(const std::vector<Ciphertext> &encrypteds, Ciphertext &destination);

        /**
        Subtracts two ciphertexts. This function computes the difference of encrypted1 and encrypted2, and stores the
        result in encrypted1.

        @param[in] encrypted1 The ciphertext to subtract from
        @param[in] encrypted2 The ciphertext to subtract
        @throws std::invalid_argument if encrypted1 or encrypted2 is not valid for the encryption parameters
        @throws std::invalid_argument if encrypted1 and encrypted2 are in different NTT forms
        @throws std::invalid_argument if encrypted1 and encrypted2 are at different level or scale
        @throws std::logic_error if result ciphertext is transparent
        */
        void sub_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);

        /**
        Subtracts two ciphertexts. This function computes the difference of encrypted1 and encrypted2 and stores the
        result in the destination parameter.

        @param[in] encrypted1 The ciphertext to subtract from
        @param[in] encrypted2 The ciphertext to subtract
        @param[out] destination The ciphertext to overwrite with the subtraction result
        @throws std::invalid_argument if encrypted1 or encrypted2 is not valid for the encryption parameters
        @throws std::invalid_argument if encrypted1 and encrypted2 are in different NTT forms
        @throws std::invalid_argument if encrypted1 and encrypted2 are at different level or scale
        @throws std::logic_error if result ciphertext is transparent
        */
        inline void sub(const Ciphertext &encrypted1, const Ciphertext &encrypted2, Ciphertext &destination)
        {
            if (&encrypted2 == &destination)
            {
                sub_inplace(destination, encrypted1);
                negate_inplace(destination);
            }
            else
            {
                destination = encrypted1;
                sub_inplace(destination, encrypted2);
            }
        }


    private:

        CGSWContext context_;

    };
}