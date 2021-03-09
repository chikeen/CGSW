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

        for(int k = 0; k < l; k++){
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