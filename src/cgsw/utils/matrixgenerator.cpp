//
// Created by Chi Keen Tan on 24/12/2020.
//

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include "matrixgenerator.h"


namespace cgsw {

    namespace util {

        MatrixGenerator::MatrixGenerator() {
            // TODO:- move this somewhere
            srand((unsigned) time(0));
//            std::cout << "RAND_MAX:" << RAND_MAX << std::endl;
        }

        dynMatrix MatrixGenerator::gen_random_matrix(size_t rows, size_t cols, uint64_t modulus) {
            /*
             * Method 1: use eigen own random generator then apply modulo function (using this now)
             * Method 2: use <random> random generator + modulo function
             */
            std::cout << "gen_random_matrix: rows " << rows << ", cols:" << cols << ", modulus:" << modulus << std::endl;
            dynMatrix random_matrix = dynMatrix::Random(rows, cols);
//            std::cout <<"random_matrix" << random_matrix << std::endl;
            random_matrix = random_matrix.unaryExpr([&](const int x) { return x % modulus; });
//            std::cout << random_matrix << std::endl;
            return random_matrix;
        }

        dynMatrix MatrixGenerator::gen_empty_matrix(size_t rows, size_t cols) {
            return dynMatrix(rows, cols);
        }

        dynMatrix MatrixGenerator::gen_normal_matrix(size_t rows, size_t cols, uint64_t modulus) {
            std::cout << "gen_normal_matrix: rows " << rows << ", cols:" << cols << ", modulus:" << modulus << std::endl;
            const int mean = 0;
            const double stddev = 2.0;// TODO:- how to calculate the standard deviation?

            dynMatrix normal_matrix(rows, cols);

            std::default_random_engine generator;
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

        }

        dynMatrix MatrixGenerator::gen_gadget_matrix(size_t rows, size_t cols) {
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
        }

        dynMatrix MatrixGenerator::gen_uniform_matrix(size_t rows, size_t cols, uint64_t modulus) {

        }


    }
}