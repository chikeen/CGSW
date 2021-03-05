//
// Created by Chi Keen Tan on 17/12/2020.
//
#pragma once

#include "common.h"
#include "encryptionparams.h"

namespace cgsw {

    class Ciphertext {

        public:
            Ciphertext(){};

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

            void set_data(CGSW_mat data_in) {
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
            CGSW_mat data_;

            std::size_t size_ = 0;
    };
}