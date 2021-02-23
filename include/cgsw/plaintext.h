//
// Created by Chi Keen Tan on 19/12/2020.
//

#pragma once


#include "common.h"
#include "encryptionparams.h"

namespace cgsw {

    class Plaintext {

        public:
//            Plaintext(const EncryptionParameters &params){}; //TODO:- how to convert this into a matrix //
            Plaintext(uint64_t data_in):data_(data_in){}
            Plaintext(){};

            inline void set_data(matrixElemType data){
                data_ = data;
            }

            inline auto &data() noexcept
            {
                return data_;
            }

            inline auto &data() const noexcept
            {
                return data_;
            }


        private:

            matrixElemType data_;


    };


    class CGSWPlaintext {
        public:
    //            Plaintext(const EncryptionParameters &params){}; //TODO:- how to convert this into a matrix //
            CGSWPlaintext(EncryptionParameters params, dynUintMatrix data_in):data_(data_in), params_(params){};

            CGSWPlaintext(){};

            inline void set_data(dynUintMatrix data){
                data_ = data;
            }

            inline auto &data() noexcept
            {
                return data_;
            }

            inline auto &data() const noexcept
            {
                return data_;
            }

            inline auto &bit_decomposed_data() noexcept{
                return bit_decomposed_data_;
            }

            inline auto &bit_decomposed_data() const noexcept
            {
                return bit_decomposed_data_;
            }

            void generate_bit_decomposed_plaintexts();


        private:

            dynUintMatrix data_;

            std::vector<dynUintMatrix> bit_decomposed_data_;

            EncryptionParameters params_;
    };


}




