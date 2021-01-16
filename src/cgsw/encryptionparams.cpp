//
// Created by Chi Keen Tan on 16/12/2020.
//


#include <cstdint>
#include <cmath>
#include "encryptionparams.h"
#include "utils/numth.h"


namespace cgsw {

    void EncryptionParameters::compute_parms_id() {
        return;
    }

    void EncryptionParameters::compute_parms() {

        //TODO:- add a bunch of condition checking and if statement to select the proper params
        // TODO:- set modulus properly with a good random prime
//        q:  5429093  k: 24  l:  23#
        lattice_dimension_ = sec_level_;
        l_ = ceil(log2(modulus_));
        m_ = lattice_dimension_ * l_;

    }

    size_t EncryptionParameters::getDepth() const {
        return depth_;
    }

    uint64_t EncryptionParameters::getSecLevel() const {
        return sec_level_;
    }

    uint64_t EncryptionParameters::getModulus() const {
        return modulus_;
    }

    uint64_t EncryptionParameters::getLatticeDimension() const {
        return lattice_dimension_;
    }

    uint64_t EncryptionParameters::getM() const {
        return m_;
    }

    uint64_t EncryptionParameters::getL() const {
        return l_;
    }

    uint64_t EncryptionParameters::getErrorDist() const {
        return error_dist_;
    }

}
