//
// Created by Chi Keen Tan on 19/12/2020.
//

#pragma once


#include "common.h"

namespace cgsw {

    class Plaintext {

        public:
//            Plaintext(const EncryptionParameters &params){}; //TODO:- how to convert this into a matrix ?

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






}




