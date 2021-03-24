//
// Created by Chi Keen Tan on 02/02/2021.
//

#pragma once

#include "../common.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

namespace cgsw {
    namespace util {


        /// Variant 1:

        // Equivalent to G-1 described in PFW - like variant
        void bit_decompose_matrix(CGSW_mat& mat_out, const CGSW_mat& mat_in, uint64_t l);

        void gen_g_gadget_matrix(CGSW_mat& mat, size_t n, size_t m);

        /// Variant 2:

        // takes in q, and generate
        void gen_f_prime(CGSW_mat& mat, size_t p, size_t t);

        void gen_f_trapdoor_matrix(CGSW_mat& mat, uint64_t p, uint64_t t);

        void gen_h_gadget_matrix(CGSW_mat& mat, uint32_t t);

        void h_inverse();

        void f_inverse();
    }
}