//
// Created by Chi Keen Tan on 19/12/2020.
//

#include "../../include/cgsw/plaintext.hpp"
#include "../../include/cgsw/encryptionparams.hpp"


namespace cgsw {

    void CGSWPlaintext::generate_bit_decomposed_plaintexts() {
        // from data_ -> bit_decomposed_data_

        uint64_t rows = data_.NumRows(),
                 cols = data_.NumCols();

        for(int k = 0; k < params_.getPL(); k++){
            CGSW_mat_uint tmp;
            tmp.SetDims(rows, cols);
            for (int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++) {
                    tmp[i][j] = bit(data_[i][j], k);
                }
            }

            bit_decomposed_data_.push_back(tmp);
        }
    }
}