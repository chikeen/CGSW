//
// Created by Chi Keen Tan on 17/12/2020.
//
#pragma once

#include "common.h"
#include "encryptionparams.h"
#include "context.h"

namespace cgsw {

    /**
    Class to store a ciphertext element. The data for a ciphertext consists
    of two or more polynomials, which are in Microsoft SEAL stored in a CRT
    form with respect to the factors of the coefficient modulus. This data
    itself is not meant to be modified directly by the user, but is instead
    operated on by functions in the Evaluator class. The size of the backing
    array of a ciphertext depends on the encryption parameters and the size
    of the ciphertext (at least 2). If the poly_modulus_degree encryption
    parameter is N, and the number of primes in the coeff_modulus encryption
    parameter is K, then the ciphertext backing array requires precisely
    8*N*K*size bytes of memory. A ciphertext also carries with it the
    parms_id of its associated encryption parameters, which is used to check
    the validity of the ciphertext for homomorphic operations and decryption.

    @par Memory Management
    The size of a ciphertext refers to the number of polynomials it contains,
    whereas its capacity refers to the number of polynomials that fit in the
    current memory allocation. In high-performance applications unnecessary
    re-allocations should be avoided by reserving enough memory for the
    ciphertext to begin with either by providing the desired capacity to the
    constructor as an extra argument, or by calling the reserve function at
    any time.

    @par Thread Safety
    In general, reading from ciphertext is thread-safe as long as no other
    thread is concurrently mutating it. This is due to the underlying data
    structure storing the ciphertext not being thread-safe.

    @see Plaintext for the class that stores plaintexts.
    */
    class Ciphertext {

        public:
            Ciphertext();

            Ciphertext& operator=(const Ciphertext& other)
            {
                if (this != &other) // not a self-assignment
                {
                    data_ = other.data_;
                }
                return *this;
            }

            inline std::size_t size() const noexcept
            {
                return size_;
            }

            void set_data(dynMatrix data_in) {
                data_ = data_in;
            }

            inline auto &data() noexcept
            {
                return data_;
            }

            inline auto &data() const noexcept
            {
                return data_;
            }




    private:
            dynMatrix data_;

            std::size_t size_ = 0;
    };
}