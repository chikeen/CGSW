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

        inline matrixLongElemType gen_prime(size_t bits){
            // A (Sophie) Germain prime is a prime p such that p' = 2*p+1 is also a prime.
            // Such primes are useful for cryptographic applications...cryptographers
            // sometimes call p' a "strong" or "safe" prime.
            // GenGermainPrime generates a random Germain prime n of length l
            // so that the probability that either n or 2*n+1 is not a prime
            // is bounded by 2^(-err).
            return NTL::GenGermainPrime_ZZ(bits);
        }

    } // namespace util
} // namespace cgsw


