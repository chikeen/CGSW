//
// Created by Chi Keen Tan on 17/12/2020.
//

#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <NTL/ZZ_p.h>
#include <NTL/vec_ZZ_p.h>
#include <vector>
#include <unordered_map>
#include <NTL/matrix.h>
#include <NTL/mat_ZZ_p.h>
#include <NTL/tools.h>
#include "global.hpp"


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

class NotSupported : public std::logic_error {
    public:
        NotSupported() : std::logic_error("Current schemes doesn't not support this function") {};
};

// NTL extensions
namespace NTL {
    inline CGSW_long sqrt(const CGSW_long &x){
        return SqrRoot(x);
    }

    inline double log2(const CGSW_long &x){
        double tmp = log(x);
        double tmp2 = log10(2);
        return log(x) / log(CGSW_long (2));
    }

    inline CGSW_mat_uint operator+(const CGSW_mat_uint &a, const CGSW_mat_uint &b){
        assert(a.NumCols() == b.NumCols());
        assert(a.NumRows() == b.NumRows());

        CGSW_mat_uint ans;
        ans.SetDims(a.NumRows(), a.NumCols());
        for (auto i = 0; i < a.NumRows(); i ++){
            for (auto j = 0; j < a.NumCols(); j ++){
                ans[i][j] = a[i][j] + b[i][j];
            }
        }

        return ans;
    }

    inline CGSW_mat_uint operator-(const CGSW_mat_uint &a, const CGSW_mat_uint &b){
        assert(a.NumCols() == b.NumCols());
        assert(a.NumRows() == b.NumRows());

        CGSW_mat_uint ans;
        ans.SetDims(a.NumRows(), a.NumCols());
        for (auto i = 0; i < a.NumRows(); i ++){
            for (auto j = 0; j < a.NumCols(); j ++){
                ans[i][j] = a[i][j] - b[i][j];
            }
        }

        return ans;
    }

// This is temporary scaffolding for cgsw2 encryption params
}