//
// Created by Chi Keen Tan on 17/12/2020.
//

#pragma once

#include <iostream>
#include "thirdparty/Eigen/Dense"
#include "thirdparty/Eigen/Core"
#include <NTL/ZZ.h>
#include <NTL/tools.h>


// Common typedef

typedef NTL::ZZ matrixElemType;

typedef Eigen::Matrix<matrixElemType , Eigen::Dynamic, Eigen::Dynamic> dynMatrix;

// Overriding Eigen with custom scalar types: see https://eigen.tuxfamily.org/dox/TopicCustomizing_CustomScalar.html

namespace Eigen {
    template<> struct NumTraits<matrixElemType> : NumTraits<uint64_t> {
        typedef matrixElemType Real;
        typedef matrixElemType NonInteger;
        typedef matrixElemType Nested;

        enum {
            IsComplex = 0,
            IsInteger = 1,
            InSigned = 1,
            RequireInitialization = 1,
            ReadCost = 3, // arbitrary number for now
            AddCost = 10, // arbitrary number for now
            MulCost = 100, // arbitrary number for now
        };
    };
}


namespace NTL {
    inline matrixElemType sqrt(const matrixElemType & x){
        return SqrRoot(x);
    }
}

