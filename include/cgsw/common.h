//
// Created by Chi Keen Tan on 17/12/2020.
//

#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <vector>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/tools.h>


// Common typedef

typedef NTL::ZZ CGSW_long;

typedef NTL::ZZ_p CGSW_mod;

typedef NTL::vec_ZZ_p CGSW_vec;

typedef NTL::mat_ZZ_p CGSW_mat;

typedef NTL::Mat<uint64_t> CGSW_mat_uint;


// Exception Type

class NotImplemented : public std::logic_error {
    public:
        NotImplemented() : std::logic_error("Function not yet implemented") { };
};


namespace NTL {
    inline CGSW_long sqrt(const CGSW_long & x){
        return SqrRoot(x);
    }

    inline double log2(const CGSW_long & x){
        double tmp = log(x);
        double tmp2 = log10(2);
        return log(x) / log(CGSW_long (2));
    }
}