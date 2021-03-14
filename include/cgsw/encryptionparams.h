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

        // Compressed-GSW Scheme, PVW variant
        cgsw1 = 0x2,

        // Compressed-GSW scheme, nearly-square variant
        cgsw2 = 0x3
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
            EncryptionParameters(scheme_type scheme = scheme_type::none);

            inline void set_circuit_depth(size_t depth){
                depth_ = depth;
            }

            inline void set_security_level(uint64_t sec_level){
                // According to the FHE convention docs
                sec_level_ = sec_level;
            }

            inline void set_rate(double rate){
                // According to the FHE convention docs
                // Rate cannot be 1 !!!
                rate_ = rate;
            }

            void compute(){
                if(scheme_ == scheme_type::gsw){
                    compute_gsw_params();
                } else if (scheme_ == scheme_type::cgsw1){
                    compute_cgsw1_params();
                } else if (scheme_ == scheme_type::cgsw2){
                    compute_cgsw2_params();
                }
            }

            // Warning: Only used for testing
            inline void set_cipher_modulus(CGSW_long modulus){
                cipher_modulus_ = modulus;
                l_p_ = ceil(log2(cipher_modulus_));
                m_ = lattice_dimension_0_ * l_p_;
            }

            inline void set_plain_modulus(CGSW_long modulus){
                plain_modulus_ = modulus;
            }
            // getters

            size_t getDepth() const;

            uint64_t getSecLevel() const;

            CGSW_long getCipherModulus() const;

            CGSW_long getPlainModulus() const;

            uint64_t getLatticeDimension0() const;

            uint64_t getLatticeDimension1() const;

            uint64_t getLatticeDimension2() const;

            uint64_t getM() const;

            uint64_t getPL() const;

            uint64_t getQL() const;

            uint64_t getF() const;

            CGSW_mat getH() const;

            scheme_type getScheme() const;

            double getRate() const;

            friend std::ostream& operator<<(std::ostream& os, const EncryptionParameters& encp);

            /**
            Returns the encryption scheme type.
            */
            inline scheme_type scheme() const noexcept{
                return scheme_;
            }

            void find_cgsw2_modulus(uint64_t sec_level, double rate);


        private:

            void set_cgsw_modulus();



            void compute_gsw_params();

            void compute_cgsw1_params();

            void compute_cgsw2_params();

            // encryption params
            scheme_type scheme_;

            size_t depth_;

            uint64_t sec_level_;

            CGSW_long cipher_modulus_; // q

            uint64_t lattice_dimension_0_; // n_0

            uint64_t lattice_dimension_1_; // n_1

            uint64_t lattice_dimension_2_; // n_1

            uint64_t m_; // m = n log q

            uint64_t l_p_; // no of bits in plaintext modulus

            uint64_t l_q_; // no of bits in ciphertext modulus

            // Only CGSW --------

            double rate_;

            CGSW_long plain_modulus_; // p

            uint64_t f_; // f = round (q/p)

            CGSW_mat H_;

            //TODO:- fix l_p and l_q distinction

    };
}
