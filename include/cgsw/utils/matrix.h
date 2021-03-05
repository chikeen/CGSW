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
         * Matrix/vector related:
         */

//        // Should rarely use this now
//        inline CGSW_mat modulo_matrix(CGSW_mat & mat, CGSW_mod modulus){
//            throw (NotImplemented());
//        }
//
//        inline CGSW_mat_uint modulo_matrix(CGSW_mat_uint& mat, uint64_t modulus){
//            throw (NotImplemented());
//        }

        void bit_decompose_matrix(CGSW_mat& mat_out, const CGSW_mat& mat_in, uint64_t l);

        void gen_random_matrix(CGSW_mat& mat, size_t n, size_t m);

        void gen_random_matrix(CGSW_mat& mat, size_t n, size_t m, size_t limit);

        void gen_random_uint_matrix(CGSW_mat_uint& mat,  size_t n, size_t m, size_t range);

        void gen_empty_matrix(CGSW_mat& mat, size_t n, size_t m);

        void gen_identity_matrix(CGSW_mat& mat, size_t n, size_t m);

        void gen_normal_matrix(CGSW_mat& mat, size_t n, size_t m);

        void gen_gadget_matrix(CGSW_mat& mat, size_t n, size_t m);

        void concat_matrix_h(CGSW_mat& mat_out, const CGSW_mat& mat_a, const CGSW_mat& mat_b);

        void concat_matrix_h(CGSW_mat& mat_out, const CGSW_mat& mat_a, const CGSW_vec& vec_b);

        void concat_matrix_v(CGSW_mat& mat_out, const CGSW_mat& mat_a, const CGSW_mat& mat_b);

        CGSW_mod get_norm(const CGSW_mat& mat);

        CGSW_mod get_norm(const CGSW_vec& vec);

        CGSW_long get_sum(const CGSW_mat& mat);

//        // can't we use normal gen_random?
//        void gen_random_uint_matrix(CGSW_mat_uint& mat,  size_t n, size_t m, size_t range);


    } // util
} // cgsw
