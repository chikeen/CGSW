//
// Created by Chi Keen Tan on 19/12/2020.
//

#include "../../include/cgsw/plaintext.h"
#include "../../include/cgsw/encryptionparams.h"


namespace cgsw {

    void CGSWPlaintext::generate_bit_decomposed_plaintexts() {
        // from data_ -> bit_decomposed_data_

        uint l = ceil(log2(params_.getPlainModulus())); // l = no of decomposed plaintexts matrices
        uint64_t rows = data_.NumRows(),
                 cols = data_.NumCols();

//        TODO:-
//        bit_decomposed_data_ = std::vector<CGSW_mat_uint>(l, dynUintMatrix::Zero(rows, cols));
//
//        for(int k = 0; k < l; k++){
//            for (int i = 0; i < rows; i++){
//                for(int j = 0; j < cols; j++) {
//                    bit_decomposed_data_[k](i, j) = bit(data_(i, j), k);
//                }
//            }
//        }
    }
}