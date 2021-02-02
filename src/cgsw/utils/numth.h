//
// Created by Chi Keen Tan on 16/12/2020.
// Containing all number theory utils function
//

#pragma once

#include "../common.h"

using namespace NTL;

// TODO:- support 128, 192, 256 bit prime number

namespace cgsw {
    namespace util {

        bool is_prime(const uint64_t value, size_t num_rounds);

        uint64_t get_prime(int bit_size);


    } // namespace util
} // namespace cgsw


