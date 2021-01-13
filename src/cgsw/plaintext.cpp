//
// Created by Chi Keen Tan on 19/12/2020.
//

#include "plaintext.h"


namespace cgsw {

    Plaintext::Plaintext(const CGSWContext &context, const int data_in) {

        // get length of array == plaintext space
        int length = context.parms().getModulus();

//        // from data_in = 6 -> [0 0 0 0 0 0 6 ... 0 0 ]
//        data_ = dynMatrix(1, length);
//        data_(0, data_in) = 1;
        data_ = data_in;

//        std::cout << data_ << std::endl;
    }
}