//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include <cstdint>
#include <vector>
#include "utils/numth.h"

namespace cgsw {

    /**
    Describes the type of encryption scheme to be used.
    */
    enum class scheme_type : std::uint8_t
    {
        // No scheme set; cannot be used for encryption
        none = 0x0,

        // GSW13 scheme
        gsw = 0x1,

        // Ring-GSW scheme
        rgsw = 0x2,

        // Compressed-GSW scheme
        cgsw = 0x3
    };


    /**
     * Encryption Params
     * Stores a set of attributes (qualifiers) of a set of encryption parameters.
     * Given a security_level (k), rate_of_compression, we derive the parameters as follows:
     * p =
    */
    class EncryptionParameters {

        public:

            /**
            Creates an empty set of encryption parameters.

            @param[in] scheme The encryption scheme to be used
            @see scheme_type for the supported schemes
            */
            EncryptionParameters(scheme_type scheme = scheme_type::none) : scheme_(scheme)
            {
                depth_ = 0;
                sec_level_ = 64; //default
            }

            inline void set_circuit_depth(size_t depth){
                depth_ = depth;
//                compute_parms();
            }

            inline void set_security_level(uint64_t sec_level){
                // According to the FHE convention docs
                sec_level_ = sec_level;
                compute_parms();
            }

            // Optional setters
            inline void set_modulus(matrixElemType modulus){
                modulus_ = modulus;
                l_ = ceil(log2(modulus_));
                m_ = lattice_dimension_ * l_;
            }
            // getters

            size_t getDepth() const;

            uint64_t getSecLevel() const;

            matrixElemType getModulus() const;

            uint64_t getLatticeDimension() const;

            uint64_t getM() const;

            uint64_t getL() const;


            /**
            Returns the encryption scheme type.
            */
            inline scheme_type scheme() const noexcept
            {
                return scheme_;
            }


        private:

            void compute_parms();

            // encryption params
            scheme_type scheme_;

            size_t depth_;

            uint64_t sec_level_;

            matrixElemType modulus_; // q, also equal to plaintext modulus

            uint64_t lattice_dimension_; //n,

            uint64_t m_; // m = n log q

            uint64_t l_;

    };
}
