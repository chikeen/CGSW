//
// Created by Chi Keen Tan on 24/03/2021.
//

#pragma once

// Contains some global config variables

namespace cgsw::config{

    // Keygenerator
    inline constexpr uint32_t g_cgsw1_modulus_constant {5};

    // Constructor (matrix.cpp)
    inline constexpr double g_gaussian_stddev {0};
    // TODO:- how to calculate the standard deviation?
    //TODO:- temperorary setting stddev to 0 meaning no noise

}