//
// Created by Chi Keen Tan on 24/12/2020.
//

#pragma once
#include "../thirdparty/Eigen/dense"

typedef Eigen::Matrix<uint64_t, Eigen::Dynamic, Eigen::Dynamic> dynMatrix;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> dynFMatrix;

//typedef Eigen::Matrix<cgsw::Modulus, Eigen::Dynamic, Eigen::Dynamic> dynModulusMatrix;

namespace cgsw {

    namespace util {

        class MatrixGenerator {

            public:
                MatrixGenerator();

                //TODO:- implement own random generator
                /**
                 * Currently using Eigen built-in random generator
                 * @param rows
                 * @param cols
                 * @param modulus
                 * @return
                 */
                dynMatrix gen_random_matrix(size_t rows, size_t cols, uint64_t modulus);

                dynMatrix gen_empty_matrix(size_t rows, size_t cols);

                dynMatrix gen_normal_matrix(size_t rows, size_t cols, uint64_t modulus);

                dynMatrix gen_uniform_matrix(size_t rows, size_t cols, uint64_t modulus);

                dynMatrix gen_gadget_matrix(size_t rows, size_t cols);

            private:

        };
    }
}