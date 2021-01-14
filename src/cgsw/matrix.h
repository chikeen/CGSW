//
// Created by Chi Keen Tan on 12/01/2021.
//
#pragma once

#include "common.h"
#include "thirdparty/Eigen/dense"

typedef Eigen::Matrix<uint64_t, Eigen::Dynamic, Eigen::Dynamic> dynMatrix;
//typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> dynFMatrix;
//typedef Eigen::Matrix<cgsw::Modulus, Eigen::Dynamic, Eigen::Dynamic> dynModulusMatrix;

namespace cgsw {

    class Matrix {
        public:

            Matrix() = default;

            Matrix(dynMatrix m):data_(m){}

            Matrix(size_t rows, size_t cols);

            dynMatrix data() const{
                return data_;
            }

//            // Operator overloading: +, *, - , /, %, negate, concatenation?
//            Matrix operator+(const Matrix & a, const Matrix & b){
//                return Matrix(a.data() + b.data());
//            }

        private:

            dynMatrix data_;

            uint64_t modulus_;


    };
}