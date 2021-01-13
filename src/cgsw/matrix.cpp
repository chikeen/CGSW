//
// Created by Chi Keen Tan on 12/01/2021.
//

#include "matrix.h"


namespace cgsw {

    Matrix::Matrix(size_t rows, size_t cols){
        data_ = dynMatrix (rows, cols);
    }


}