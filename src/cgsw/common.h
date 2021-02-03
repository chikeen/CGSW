//
// Created by Chi Keen Tan on 17/12/2020.
//

#pragma once

#include <iostream>
#include "thirdparty/Eigen/Dense"
#include <NTL/ZZ.h>
#include <NTL/tools.h>


// Common typedef
typedef NTL::ZZ matrixLongElemType;

typedef uint64_t matrixElemType;

typedef Eigen::Matrix<matrixElemType , Eigen::Dynamic, Eigen::Dynamic> dynMatrix;




