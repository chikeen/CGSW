//
// Created by Chi Keen Tan on 16/12/2020.
// Containing all number theory utils function
//

#pragma once
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <tuple>
#include <vector>

using namespace std;

// TODO:- support 128, 192, 256 bit prime number

namespace cgsw {
    namespace util {


        bool is_prime(const uint64_t value, size_t num_rounds);

        // Notes that here ntt_size corresponds to poly_modulus_degree: we use (1024, 2048, 4096, 8192, 16384, or 32768).
        vector<uint64_t>get_primes(size_t ntt_size, int bit_size, size_t count);

//        uint64_t get_prime(size_t ntt_size, int bit_size);

        uint64_t get_prime(int bit_size);

        uint64_t get_sophie_germain_prime(size_t ntt_size, int bit_size);

        uint64_t get_safe_prime(uint64_t b);


    } // namespace util
} // namespace cgsw


