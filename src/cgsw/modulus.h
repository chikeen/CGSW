//
// Created by Chi Keen Tan on 18/12/2020.
//

#pragma once


#include "thirdparty/Eigen/dense"

namespace cgsw {

    class Modulus {
        
        public:

            /**
            Creates a Modulus instance. The value of the Modulus is set to
            the given value, or to zero by default.
    
            @param[in] value The integer modulus
            @throws std::invalid_argument if value is 1 or more than 61 bits
            */
            Modulus(std::uint64_t value = 0)
            {
                value_ = value;
            }

            /*
            @param[in] value The new integer modulus
            @throws std::invalid_argument if value is 1 or more than 61 bits
            */
            inline Modulus &operator=(std::uint64_t value)
            {
                value_ = value;
                return *this;
            }

            /**
            Returns the value of the current Modulus.
            */
            inline std::uint64_t value() const noexcept
            {
                return value_;
            }

//            /**
//            Returns the Barrett ratio computed for the value of the current Modulus.
//            The first two components of the Barrett ratio are the floor of 2^128/value,
//            and the third component is the remainder.
//            */
//            inline auto &const_ratio() const noexcept
//            {
//                return const_ratio_;
//            }

            /**
            Returns whether the value of the current Modulus is zero.
            */
            inline bool is_zero() const noexcept
            {
                return value_ == 0;
            }

            /**
            Returns whether the value of the current Modulus is a prime number.
            */
            inline bool is_prime() const noexcept
            {
                return is_prime_;
            }

            /**
            Returns the significant bit count of the value of the current Modulus.
            */
            inline int bit_count() const noexcept
            {
                return bit_count_;
            }
    
            /**
            Compares two Modulus instances.
    
            @param[in] compare The Modulus to compare against
            */
            inline bool operator==(const Modulus &compare) const noexcept
            {
                return value_ == compare.value_;
            }
    
            /**
            Compares a Modulus value to an unsigned integer.
    
            @param[in] compare The unsigned integer to compare against
            */
            inline bool operator==(std::uint64_t compare) const noexcept
            {
                return value_ == compare;
            }
    
            /**
            Compares two Modulus instances.
    
            @param[in] compare The Modulus to compare against
            */
            inline bool operator!=(const Modulus &compare) const noexcept
            {
                return !operator==(compare);
            }
    
            /**
            Compares a Modulus value to an unsigned integer.
    
            @param[in] compare The unsigned integer to compare against
            */
            inline bool operator!=(std::uint64_t compare) const noexcept
            {
                return !operator==(compare);
            }
    
            /**
            Compares two Modulus instances.
    
            @param[in] compare The Modulus to compare against
            */
            inline bool operator<(const Modulus &compare) const noexcept
            {
                return value_ < compare.value_;
            }
    
            /**
            Compares a Modulus value to an unsigned integer.
    
            @param[in] compare The unsigned integer to compare against
            */
            inline bool operator<(std::uint64_t compare) const noexcept
            {
                return value_ < compare;
            }
    
            /**
            Compares two Modulus instances.
    
            @param[in] compare The Modulus to compare against
            */
            inline bool operator<=(const Modulus &compare) const noexcept
            {
                return value_ <= compare.value_;
            }
    
            /**
            Compares a Modulus value to an unsigned integer.
    
            @param[in] compare The unsigned integer to compare against
            */
            inline bool operator<=(std::uint64_t compare) const noexcept
            {
                return value_ <= compare;
            }
    
            /**
            Compares two Modulus instances.
    
            @param[in] compare The Modulus to compare against
            */
            inline bool operator>(const Modulus &compare) const noexcept
            {
                return value_ > compare.value_;
            }
    
            /**
            Compares a Modulus value to an unsigned integer.
    
            @param[in] compare The unsigned integer to compare against
            */
            inline bool operator>(std::uint64_t compare) const noexcept
            {
                return value_ > compare;
            }
    
            /**
            Compares two Modulus instances.
    
            @param[in] compare The Modulus to compare against
            */
            inline bool operator>=(const Modulus &compare) const noexcept
            {
                return value_ >= compare.value_;
            }
    
            /**
            Compares a Modulus value to an unsigned integer.
    
            @param[in] compare The unsigned integer to compare against
            */
            inline bool operator>=(std::uint64_t compare) const noexcept
            {
                return value_ >= compare;
            }


        private:
            std::uint64_t value_ = 0;

            int bit_count_ = 0; //TODO:- how to set bit_count using barrett ratio ?

            bool is_prime_ = false;

        
    };
}