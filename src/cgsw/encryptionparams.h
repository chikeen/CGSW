//
// Created by Chi Keen Tan on 16/12/2020.
//

#pragma once

#include <cstdint>
#include <vector>
#include "modulus.h"
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
                sec_level_ = 0;
            }

            inline void set_circuit_depth(size_t depth){
                depth_ = depth;
                compute_parms();
            }

            inline void set_security_level(uint64_t sec_level){
                // According to the FHE convention docs
                sec_level_ = sec_level;
                compute_parms();
            }

            // getters

            size_t getDepth() const;

            uint64_t getSecLevel() const;

            uint64_t getModulus() const;

            uint64_t getLatticeDimension() const;

            uint64_t getM() const;

            uint64_t getErrorDist() const;

//
//            inline void set_poly_modulus_degree(std::size_t poly_modulus_degree)
//            {
//                if (scheme_ == scheme_type::none && poly_modulus_degree)
//                {
//                    throw std::logic_error("poly_modulus_degree is not supported for this scheme");
//                }
//
//                // Set the degree
//                poly_modulus_degree_ = poly_modulus_degree;
//
//                // Re-compute the parms_id
//                compute_parms_id();
//            }
//
//
//            inline void set_ciphertext_modulus(const std::vector<Modulus> &coeff_modulus)
//            {
//                // Check that a scheme is set
//                if (scheme_ == scheme_type::none)
//                {
//                    if (!coeff_modulus.empty())
//                    {
//                        throw std::logic_error("coeff_modulus is not supported for this scheme");
//                    }
//                }
////                else if (coeff_modulus.size() > SEAL_COEFF_MOD_COUNT_MAX || coeff_modulus.size() < SEAL_COEFF_MOD_COUNT_MIN)
////                {
////                    throw std::invalid_argument("coeff_modulus is invalid");
////                }
//
//                coeff_modulus_ = coeff_modulus;
//
//                // Re-compute the parms_id
//                compute_parms_id();
//            }
//
//
//            inline void set_plain_modulus(const Modulus &plain_modulus)
//            {
//                // Check that scheme is GSW
//                if (scheme_ != scheme_type::gsw && !plain_modulus.is_zero())
//                {
//                    throw std::logic_error("plain_modulus is not supported for this scheme");
//                }
//
//                plain_modulus_ = plain_modulus;
//
//                // Re-compute the parms_id
//                compute_parms_id();
//            }
//
//
//            inline void set_plain_modulus(std::uint64_t plain_modulus)
//            {
//                set_plain_modulus(Modulus(plain_modulus));
//                plain_modulus_in_bits_ = plain_modulus;
//            }

            /**
            Returns the encryption scheme type.
            */
            inline scheme_type scheme() const noexcept
            {
                return scheme_;
            }

//            /**
//            Returns the degree of the polynomial modulus parameter.
//            */
//            inline std::size_t poly_modulus_degree() const noexcept
//            {
//                return poly_modulus_degree_;
//            }
//
//            /**
//            Returns a const reference to the currently set coefficient modulus parameter.
//            */
//            inline auto coeff_modulus() const noexcept -> const std::vector<Modulus> &
//            {
//                return coeff_modulus_;
//            }
//
//            /**
//            Returns a const reference to the currently set plaintext modulus parameter.
//            */
//            inline const Modulus &plain_modulus() const noexcept
//            {
//                return plain_modulus_;
//            }
//
//            inline const uint64_t &plain_modulus_in_bits() const noexcept
//            {
//                return plain_modulus_in_bits_;
//            }

//            /**
//            Returns a pointer to the random number generator factory to use for encryption.
//            */
//            inline auto random_generator() const noexcept -> std::shared_ptr<UniformRandomGeneratorFactory>
//            {
//                return random_generator_;
//            }


        private:

            void compute_parms_id();

            void compute_parms();

            // encryption params
            scheme_type scheme_;

            size_t depth_;

            uint64_t sec_level_;

            uint64_t modulus_; // q, also equal to plaintext modulus

            uint64_t lattice_dimension_; //n,

            uint64_t m_; // m = n log q TODO:- come out with better naming for this

            uint64_t error_dist_; //? TODO:- create a datatype to represent this
//
//            std::size_t poly_modulus_degree_ = 0; // what is this for again?
//
//            std::vector<Modulus> coeff_modulus_{}; // ! for Ring GSW
//
//            Modulus plain_modulus_{}; // plaintext modulus
//
//            uint64_t plain_modulus_in_bits_;


    };
}


//            uint32_t k_; // security parameter, k
//
//            uint64_t p_; // ciphertext moduli
//
//            uint64_t q_; // plaintext moduli
//
//            uint32_t l_; // ceil[log(p)]
//
//            uint32_t n_; // no of gadget matrix cols
//
//            uint32_t m_; // no of gadget matrix rows
