//
// Created by Chi Keen Tan on 17/12/2020.
//
#pragma once

#include "common.h"
#include "utils/utils.h"
#include "encryptionparams.h"
#include "ciphertext.h"

namespace cgsw {

    class Evaluator{

    public:

        Evaluator(const EncryptionParameters &params);
        
        void negate_inplace(Ciphertext &encrypted);
        
        inline void negate(const Ciphertext &encrypted, Ciphertext &destination)
        {
            destination = encrypted;
            negate_inplace(destination);
        }
        
        void add_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);
        
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
        
        void add_many(const std::vector<Ciphertext> &encrypteds, Ciphertext &destination);
        
        void sub_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);
        
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

        void multiply_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2);

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