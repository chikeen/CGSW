//
// Created by Chi Keen Tan on 16/12/2020.
//


#include <cstdint>
#include <cmath>
#include "../../include/cgsw/encryptionparams.h"
#include "../../include/cgsw/utils/numth.h"


namespace cgsw {

    void EncryptionParameters::compute_parms() {

        if (scheme_ == scheme_type::gsw){

            lattice_dimension_0_ = sec_level_;
            lattice_dimension_1_ = lattice_dimension_0_ + 1;
            cipher_modulus_ = util::gen_prime(sec_level_);
            l_ = ceil(log2(cipher_modulus_));
            m_ = lattice_dimension_0_ * l_;
        }
        else if (scheme_ == scheme_type::cgsw){
            double epsilon = 1 - rate_;

            lattice_dimension_0_ = ceil(sec_level_ * 2 / epsilon);
            lattice_dimension_1_ = lattice_dimension_0_ + sec_level_;
            cipher_modulus_bit_ = plain_modulus_bit_ +  1/epsilon;

            plain_modulus_ = util::gen_prime(plain_modulus_bit_);
            cipher_modulus_ = util::gen_prime(cipher_modulus_bit_);

            l_ = ceil(log2(cipher_modulus_));
            m_ = lattice_dimension_0_ * l_;

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

    uint64_t EncryptionParameters::getLatticeDimension0() const {
        return lattice_dimension_0_;
    }

    uint64_t EncryptionParameters::getLatticeDimension1() const {
        return lattice_dimension_1_;
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

    std::ostream& operator<<(std::ostream& os, const EncryptionParameters& parms){
        std::string scheme_name;
        switch (parms.getScheme())
        {
            case scheme_type::gsw:
                scheme_name = "GSW";
                os << "/" << std::endl;
                os << "| Encryption parameters :" << std::endl;
                os << "|   scheme: " << scheme_name << std::endl;
                os << "|   security level (k): " << parms.getSecLevel() << std::endl;
                os << "|   depth (d): " << parms.getDepth() << std::endl;
                os << "|   ciphertext modulus (q): " << parms.getCipherModulus() << std::endl;
                os << "|   lattice dimension (n): " << parms.getLatticeDimension0() << std::endl;
                os << "|   second lattice dimension (m): " << parms.getM() << std::endl;
                os << "\\" << std::endl;
                break;
            case scheme_type::cgsw:
                scheme_name = "CGSW, PVW variant";
                os << "/" << std::endl;
                os << "| Encryption parameters :" << std::endl;
                os << "|   scheme: " << scheme_name << std::endl;
                os << "|   security level (k): " << parms.getSecLevel() << std::endl;
                os << "|   depth (d): " << parms.getDepth() << std::endl;
                os << "|   rate (1-epsilon): " << parms.getRate() << std::endl;
                os << "|   plaintext space in bits : " << parms.getPlainModulusBit() << std::endl;
                os << "|   ciphertext space in bits: " << parms.getCipherModulusBit() << std::endl;
                os << "|   plaintext modulus (p): " << parms.getPlainModulus()<< std::endl;
                os << "|   ciphertext modulus (q): " << parms.getCipherModulus() << std::endl;
                os << "|   lattice dimension (n0, n1): " << parms.getLatticeDimension0() << ", " << parms.getLatticeDimension1() << std::endl;
                os << "|   second lattice dimension (m): " << parms.getM() << std::endl;
                os << "\\" << std::endl;
                break;
            case scheme_type::cgsw2:
                scheme_name = "CGSW, Nearly square variant";
                break;
            default:
                break;
        }

        return os;
    }

    scheme_type EncryptionParameters::getScheme() const {
        return scheme_;
    }

    uint64_t EncryptionParameters::getCipherModulusBit() const {
        return cipher_modulus_bit_;
    }

    double EncryptionParameters::getRate() const {
        return rate_;
    }

    uint64_t EncryptionParameters::getPlainModulusBit() const {
        return plain_modulus_bit_;
    }

}
