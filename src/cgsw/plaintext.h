//
// Created by Chi Keen Tan on 19/12/2020.
//

#pragma once


#include "common.h"
#include "context.h"

namespace cgsw {

    class Plaintext {

        public:
            Plaintext(const CGSWContext &context, const int data_in); //TODO:- how to convert this into a matrix ?

            Plaintext(){};
            //for eg. 6 -> [0 0 0 0 0 1 0 0

            inline auto &data() noexcept
            {
                return data_;
            }

            inline auto &data() const noexcept
            {
                return data_;
            }


        private:
//            dynMatrix data_;
            uint64_t data_;

            void to_matrix();

    };






}




