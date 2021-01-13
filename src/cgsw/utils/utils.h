//
// Created by Chi Keen Tan on 12/01/2021.
//

#pragma once

#include "../common.h"


/*
 * A collection of utility functions
 */


namespace cgsw {
    namespace util {

        /*
         * Matrix related:
         */

        inline dynMatrix modulo_matrix(dynMatrix & mat, uint64_t modulus){
            mat = mat.unaryExpr([&](const int x) { return x % modulus; });
            return mat;
        }

        inline dynMatrix negate_matrix(dynMatrix & mat, uint64_t modulus){
            mat = mat.unaryExpr([&](const int x) { return modulus - x; });
            return mat;
        }

        inline dynMatrix bit_decompose_matrix(const dynMatrix & mat, uint64_t l);

        dynMatrix gen_random_matrix(size_t rows, size_t cols, uint64_t modulus);

        dynMatrix gen_empty_matrix(size_t rows, size_t cols);

        dynMatrix gen_normal_matrix(size_t rows, size_t cols, uint64_t modulus);

        dynMatrix gen_gadget_matrix(size_t rows, size_t cols);




    } // util
} // cgsw