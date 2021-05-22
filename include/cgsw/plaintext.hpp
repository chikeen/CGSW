//
// Created by Chi Keen Tan on 19/12/2020.
//

#pragma once


#include "common.hpp"
#include "encryptionparams.hpp"

namespace cgsw {

    class GSWPlaintext {

        public:
//            Plaintext(const EncryptionParameters &params){}; //TODO:- how to convert this into a matrix //
            GSWPlaintext(uint64_t data_in): data_(data_in){};

            GSWPlaintext(){};

            inline void set_data(uint64_t data){
                data_ = data;
            }

            inline auto &data() noexcept{
                return data_;
            }

            inline auto &data() const noexcept{
                return data_;
            }


        private:

            uint64_t data_;
    };


    class CGSWPlaintext {
        public:
    //      Plaintext(const EncryptionParameters &params){}; //TODO:- how to convert this into a matrix //
            CGSWPlaintext(EncryptionParameters params, CGSW_mat_uint data_in):data_(data_in), params_(params){
                long tmp;
                NTL::conv(tmp, params.getPlainModulus());
                modulus_uint_ = tmp;
            };

            CGSWPlaintext(EncryptionParameters params):params_(params){
                long tmp;
                NTL::conv(tmp, params.getPlainModulus());
                modulus_uint_ = tmp;

                CGSW_mat_uint m;
                m.SetDims(params_.getLatticeDimension0(), params_.getLatticeDimension0());
                data_ = m;
            };


            CGSWPlaintext(){};

            inline void set_data(CGSW_mat_uint data){
                data_ = data;
            }

            inline auto &data() noexcept{
                return data_;
            }

            inline auto &data() const noexcept{
                return data_;
            }

            inline auto &bit_decomposed_data() noexcept{
                return bit_decomposed_data_;
            }

            inline auto &bit_decomposed_data() const noexcept{
                return bit_decomposed_data_;
            }

            void generate_bit_decomposed_plaintexts();

            inline bool operator==(const CGSWPlaintext &compare) const noexcept{
                return data_ == compare.data_;
            }

            inline bool operator!=(const CGSWPlaintext &compare) const noexcept{
                return data_ != compare.data_;
            }

            //TODO-: solve the p/q problem
            inline CGSWPlaintext operator+(const CGSWPlaintext &rhs){
                assert(data_.NumCols() == rhs.data().NumCols());
                assert(data_.NumRows() == rhs.data().NumRows());

                CGSW_mat_uint data;
                data.SetDims(data_.NumRows(), data_.NumCols());
                for (auto i = 0; i < data_.NumRows(); i ++){
                    for (auto j = 0; j < data_.NumCols(); j ++){
                        data[i][j] = (data_[i][j] + rhs.data()[i][j]) % modulus_uint_;
                    }
                }

                return CGSWPlaintext(params_, data);
            }

            //TODO:- solve the p/q problem
            inline CGSWPlaintext operator-(const CGSWPlaintext &rhs){
                assert(data_.NumCols() == rhs.data().NumCols());
                assert(data_.NumRows() == rhs.data().NumRows());

                CGSW_mat_uint data;
                data.SetDims(data_.NumRows(), data_.NumCols());
                for (auto i = 0; i < data_.NumRows(); i ++){
                    for (auto j = 0; j < data_.NumCols(); j ++){
                        if(data_[i][j] > rhs.data()[i][j]){
                            data[i][j] = (data_[i][j] - rhs.data()[i][j]) % modulus_uint_;
                        }
                        else{
                            data[i][j] = (modulus_uint_ + data_[i][j] - rhs.data()[i][j]) % modulus_uint_;
                        }

                    }
                }

                return CGSWPlaintext(params_, data);
            }

            inline CGSWPlaintext operator*(const CGSWPlaintext &rhs){
                assert(data_.NumCols() == rhs.data().NumRows());

                CGSW_mat_uint data;
                data.SetDims(data_.NumRows(), rhs.data().NumCols());
                for (auto i = 0; i < data_.NumRows(); i ++){
                    for (auto j = 0; j < data_.NumCols(); j ++){
                        data[i][j] = (data_[i][j] * rhs.data()[i][j]) % modulus_uint_;
                    }
                }

                return CGSWPlaintext(params_, data);
            }

            inline CGSWPlaintext operator*(const uint64_t &rhs){
                CGSW_mat_uint data;
                data.SetDims(data_.NumRows(), data_.NumCols());
                for (auto i = 0; i < data_.NumRows(); i ++){
                    for (auto j = 0; j < data_.NumCols(); j ++){
                        data[i][j] = (data_[i][j] * rhs) % modulus_uint_;
                    }
                }

                return CGSWPlaintext(params_, data);
            }

            inline auto &at(uint32_t i) {
                assert(i < params_.getNumSlots());
                return data_[i/params_.getLatticeDimension0()][i%params_.getLatticeDimension0()];
            }

            inline auto &at(uint32_t i) const {
                assert(i < params_.getNumSlots());
                return data_[i/params_.getLatticeDimension0()][i%params_.getLatticeDimension0()];
            }

        private:

            EncryptionParameters params_;

            uint64_t modulus_uint_;

            CGSW_mat_uint data_;

            std::vector<CGSW_mat_uint> bit_decomposed_data_;
    };


}




