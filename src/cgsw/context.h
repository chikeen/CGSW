//
// Created by Chi Keen Tan on 19/12/2020.
//

#pragma once


#include <cstdint>
#include <vector>

#include "encryptionparams.h"

namespace cgsw {

    class CGSWContext {

        public:

            CGSWContext() = default;

            CGSWContext(EncryptionParameters params): parms_(params){};

            /**
            Returns a const reference to the underlying encryption parameters.
            */
            inline auto &parms() const noexcept
            {
                return parms_;
            }

            /**
            Returns the significant bit count of the total coefficient modulus.
            */
            inline int total_coeff_modulus_bit_count() const noexcept
            {
                return total_coeff_modulus_bit_count_;
            }

        private:
            EncryptionParameters parms_;

            int total_coeff_modulus_bit_count_ = 0;

    };
}