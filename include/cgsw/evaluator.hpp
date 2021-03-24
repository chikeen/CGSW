//
// Created by Chi Keen Tan on 17/12/2020.
//
#pragma once

#include "cgsw/utils/utils.hpp"
#include "ciphertext.hpp"
#include "common.hpp"
#include "encryptionparams.hpp"
#include "plaintext.hpp"

namespace cgsw {

    class Evaluator{

    public:

        Evaluator(const EncryptionParameters &params);
        
        void negate_inplace(Ciphertext &encrypted);

        void add_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);

        void sub_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);

        void multiply_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);

        // CGSW1
        void add_inplace(CGSWCiphertext &encrypted1, const CGSWCiphertext &encrypted2);

        void sub_inplace(CGSWCiphertext &encrypted1, const CGSWCiphertext &encrypted2);

        void multiply_inplace_gsw(CGSWCiphertext &encrypted1, const GSWCiphertext &encrypted2);

        void multiply_inplace_plaintext(CGSWCiphertext &encrypted, const CGSWPlaintext);


        inline void negate(const Ciphertext &encrypted, Ciphertext &destination)
        {
            destination = encrypted;
            negate_inplace(destination);
        }
        
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

        inline void multiply(const Ciphertext &encrypted1, const Ciphertext &encrypted2, Ciphertext &destination){
            if (&encrypted2 == &destination)
            {
                multiply_inplace(destination, encrypted1);
            }
            else
            {
                destination = encrypted1;
                multiply_inplace(destination, encrypted2);
            }
        }

        inline void divide(const Ciphertext &encrypted1, const Ciphertext &encrypted2, Ciphertext &destination);


    private:

        EncryptionParameters params_;

    };
}