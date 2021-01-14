//
// Created by Chi Keen Tan on 12/01/2021.
//
#include "utils.h"
#include <boost/random/normal_distribution.hpp>

#include "../common.h"
//#include <boost/random.hpp>

namespace cgsw {
    namespace util{

        dynMatrix gen_random_matrix(size_t rows, size_t cols, uint64_t modulus) {
            dynMatrix random_matrix = dynMatrix::Random(rows, cols);
            modulo_matrix(random_matrix, modulus);
            return random_matrix;
        };

        dynMatrix gen_empty_matrix(size_t rows, size_t cols) {
            return dynMatrix(rows, cols);
        };

        dynMatrix gen_normal_matrix(size_t rows, size_t cols, uint64_t modulus) {
            std::random_device rd;
            const int mean = 0;
            const double stddev = 1.0;// TODO:- how to calculate the standard deviation?

            dynMatrix normal_matrix(rows, cols);

            std::default_random_engine generator;
            generator.seed(rd());
            std::normal_distribution<double> distribution(mean,stddev);
            double random_num;

            for(int i = 0; i < cols; i ++){
                for(int j = 0; j < rows; j ++){
                    // TODO:- are we sure that wrapping around modulus won't change the dist ?
                    random_num = distribution(generator);
                    if(random_num < 0) random_num = modulus + random_num;
                    normal_matrix(j, i) = (uint64_t) random_num % modulus;
                }
            }

//            std::cout << "normal_matrix" << normal_matrix << std::endl;

            return normal_matrix;
        };

        dynMatrix gen_gadget_matrix(size_t rows, size_t cols) {
            if(cols < rows) throw std::runtime_error("gadget matrix cols must > rows");

            int no_log = cols/rows;

            dynMatrix gadget_matrix = dynMatrix::Zero(rows, cols);
            for(int i = 0 ; i < rows; i++){
                for(int l = 0; l < no_log; l++){
                    gadget_matrix(i, no_log*i + l) = pow(2, l);
                }
            }

//            std::cout << "gadget_matrix" << gadget_matrix << std::endl;
            return gadget_matrix;
        };

        dynMatrix bit_decompose_matrix(dynMatrix & mat, uint64_t l){
            /*
             * Take a nxc matrix and make it mxc
             */
            uint64_t n = mat.rows();
            uint64_t c = mat.cols();
            uint64_t m = n * l;

            dynMatrix mat_return = dynMatrix (m, c);

            for(int j = 0; j < c; j ++){
                for(int i = 0; i < n; i++){
                    for(int k = 0; k < l; k++){
                        mat_return((i * l + k), j) = (mat(i, j) & (uint64_t ) pow(2, k))? 1 :0;
                    }
                }
            }

            return mat_return;
        };




    } // util
} // cgsw
