//
// Created by Chi Keen Tan on 16/12/2020.
//


#include <cstdint>
#include <cmath>
#include "encryptionparams.h"
#include "utils/numth.h"


namespace cgsw {

    void EncryptionParameters::compute_parms() {

        if (scheme_ == scheme_type::gsw){
            lattice_dimension_ = sec_level_;
            cipher_modulus_ = util::gen_prime(sec_level_);
            l_ = ceil(log2(cipher_modulus_));
            m_ = lattice_dimension_ * l_;
        }
        else if (scheme_ == scheme_type::cgsw){
            lattice_dimension_ = sec_level_;
            cipher_modulus_ = util::gen_prime(sec_level_);
            plain_modulus_ = util::gen_prime(3); // TODO:- 3 bits for now, details follows later
            l_ = ceil(log2(cipher_modulus_));
            m_ = lattice_dimension_ * l_;

            long tmp;
            conv(tmp, cipher_modulus_ / plain_modulus_);
            f_ = (uint64_t ) tmp; //TODO:- f is now floored. Implement rounding of ZZ/ZZ for greater accuracy
        }
    }

    size_t EncryptionParameters::getDepth() const {
        return depth_;
    }

    uint64_t EncryptionParameters::getSecLevel() const {
        return sec_level_;
    }

    matrixElemType EncryptionParameters::getCipherModulus() const {
        return cipher_modulus_;
    }

    matrixElemType EncryptionParameters::getPlainModulus() const {
        return plain_modulus_;
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

    uint64_t EncryptionParameters::getF() const {
        return f_;
    }

}
