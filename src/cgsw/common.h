//
// Created by Chi Keen Tan on 17/12/2020.
//

#pragma once

#include <iostream>
#include "modulus.h"
#include "utils/matrixgenerator.h"




// Common typedef

typedef Eigen::Matrix<uint64_t, Eigen::Dynamic, Eigen::Dynamic> dynMatrix;

typedef Eigen::Matrix<cgsw::Modulus, Eigen::Dynamic, Eigen::Dynamic> dynModulusMatrix;


/*
 * Ciphertext space, which have a modulo q where q
 */


// plaintext space
/*
 * Plaintext space, will have a modulo p where p << q
 */



