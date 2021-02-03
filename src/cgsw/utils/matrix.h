//
// Created by Chi Keen Tan on 02/02/2021.
//

#pragma once

#include "../common.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

namespace cgsw {
    namespace util {

        /*
         * Matrix related:
         */

        inline dynMatrix modulo_matrix(dynMatrix & mat, matrixElemType modulus){
            mat = mat.unaryExpr([&](const matrixElemType x) { return x % modulus; });
            return mat;
        }

        inline dynMatrix negate_matrix(dynMatrix & mat, matrixElemType modulus){
            mat = mat.unaryExpr([&](const matrixElemType x) { return modulus - x; });
            return mat;
        }

        dynMatrix bit_decompose_matrix(dynMatrix mat, uint64_t l);

        dynMatrix gen_random_matrix(size_t rows, size_t cols, matrixElemType modulus);

        dynMatrix gen_empty_matrix(size_t rows, size_t cols);

        dynMatrix gen_normal_matrix(size_t rows, size_t cols, matrixElemType modulus);

        dynMatrix gen_gadget_matrix(size_t rows, size_t cols);


    } // util
} // cgsw
