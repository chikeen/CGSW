//
// Created by Chi Keen Tan on 16/12/2020.
//


#include <cstdint>
#include <cmath>
#include "encryptionparams.h"
#include "utils/numth.h"


namespace cgsw {

    void EncryptionParameters::compute_parms() {

        lattice_dimension_ = sec_level_;
        modulus_ = util::gen_prime(sec_level_);
        l_ = ceil(log2(modulus_));
        m_ = lattice_dimension_ * l_;

    }

    size_t EncryptionParameters::getDepth() const {
        return depth_;
    }

    uint64_t EncryptionParameters::getSecLevel() const {
        return sec_level_;
    }

    matrixElemType EncryptionParameters::getModulus() const {
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

}
