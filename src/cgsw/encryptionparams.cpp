//
// Created by Chi Keen Tan on 16/12/2020.
//


#include <cstdint>
#include <cmath>
#include "../../include/cgsw/encryptionparams.h"
#include "../../include/cgsw/utils/numth.h"


namespace cgsw {

    EncryptionParameters::EncryptionParameters(scheme_type scheme){
            //default values
            scheme_ = scheme;
            depth_ = 0;
            sec_level_ = 64;
            rate_ = 0.8;

            // Initialisation for random operation that follows
            SetSeed((NTL::conv<NTL::ZZ>((long)time(NULL))));
    }

    size_t EncryptionParameters::getDepth() const {
        return depth_;
    }

    uint64_t EncryptionParameters::getSecLevel() const {
        return sec_level_;
    }


    CGSW_long EncryptionParameters::getCipherModulus() const {
        return cipher_modulus_;
    }

    CGSW_long EncryptionParameters::getPlainModulus() const {
        return plain_modulus_;
    }

    uint64_t EncryptionParameters::getLatticeDimension0() const {
        return lattice_dimension_0_;
    }

    uint64_t EncryptionParameters::getLatticeDimension1() const {
        return lattice_dimension_1_;
    }

    uint64_t EncryptionParameters::getLatticeDimension2() const {
        return lattice_dimension_2_;
    }

    uint64_t EncryptionParameters::getM() const {
        return m_;
    }

    uint64_t EncryptionParameters::getPL() const {
        return l_p_;
    }

    uint64_t EncryptionParameters::getQL() const {
        return l_q_;
    }


    uint64_t EncryptionParameters::getF() const {
        return f_;
    }

    scheme_type EncryptionParameters::getScheme() const {
        return scheme_;
    }

    double EncryptionParameters::getRate() const {
        return rate_;
    }

    CGSW_mat EncryptionParameters::getH() const {
        return H_;
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
                os << "|   l_p: " << parms.getPL() << std::endl;
                os << "|   l_q: " << parms.getPL() << std::endl;
                os << "|   f: " << parms.getF() << std::endl;
                os << "\\" << std::endl;
                break;
            case scheme_type::cgsw1:
                scheme_name = "CGSW, PVW variant";
                os << "/" << std::endl;
                os << "| Encryption parameters :" << std::endl;
                os << "|   scheme: " << scheme_name << std::endl;
                os << "|   security level (k): " << parms.getSecLevel() << std::endl;
                os << "|   depth (d): " << parms.getDepth() << std::endl;
                os << "|   rate (1-epsilon): " << parms.getRate() << std::endl;
                os << "|   plaintext modulus (p): " << parms.getPlainModulus()<< std::endl;
                os << "|   ciphertext modulus (q): " << parms.getCipherModulus() << std::endl;
                os << "|   lattice dimension (n0, n1): " << parms.getLatticeDimension0() << ", " << parms.getLatticeDimension1() << std::endl;
                os << "|   second lattice dimension (m): " << parms.getM() << std::endl;
                os << "|   l_p: " << parms.getPL() << std::endl;
                os << "|   l_q: " << parms.getPL() << std::endl;
                os << "|   f: " << parms.getF() << std::endl;
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


    /// Private:

    void EncryptionParameters::set_cgsw_modulus() {

        auto epsilon = 1 - rate_;
        uint64_t p_min = pow(sec_level_, 1/epsilon);
        uint64_t p = NTL::NextPrime(p_min);

        uint64_t q_min = pow(p, 1 + epsilon/2);
        uint64_t q = NTL::NextPrime(q_min);

        plain_modulus_ = p;
        cipher_modulus_ = q;
    }

    void EncryptionParameters::compute_gsw_params() {

        lattice_dimension_0_ = sec_level_;
        lattice_dimension_1_ = lattice_dimension_0_ + 1;
        plain_modulus_ = 3; //default for binary operation
        cipher_modulus_ = util::gen_prime(sec_level_);
        CGSW_mod::init(cipher_modulus_);
        l_q_ = ceil(log2(cipher_modulus_));
        m_ = lattice_dimension_1_ * l_q_;

        // TODO:- downcastting modulus, again modulus must below 64 bit
        long p, q;
        conv(p, plain_modulus_);
        conv(q, cipher_modulus_);
        f_ = util::round_division(q, p);

    }

    void EncryptionParameters::compute_cgsw1_params() {
        double epsilon = 1 - rate_;

        lattice_dimension_0_ = ceil(sec_level_ * 2 / epsilon) + 2; // + 2 so that it is larger than
        lattice_dimension_1_ = lattice_dimension_0_ + sec_level_;

        // Generate p and q modulus
        set_cgsw_modulus();

        CGSW_mod::init(cipher_modulus_);
        l_p_ = ceil(log2(plain_modulus_));
        l_q_ = ceil(log2(cipher_modulus_));
        m_ = lattice_dimension_1_ * l_q_;

        long p, q;
        conv(p, plain_modulus_);
        conv(q, cipher_modulus_);
        f_ = util::round_division(q, p);

    }

    void EncryptionParameters::compute_cgsw2_params() {
        // TODO:-
        // but it should actually be the same as cgsw1
        auto epsilon = 1 - rate_;

        lattice_dimension_0_ = rate_; // Not sure if this is correct, didn't mention in the paper
        lattice_dimension_1_ = lattice_dimension_0_ + sec_level_;
        lattice_dimension_2_ = lattice_dimension_0_ * lattice_dimension_0_
                        / (lattice_dimension_1_ * (rate_)); // require n0^2 / (n1n2) >= 1 - rate

        // cipher modulus are chosen from a list of predifined options that satisfied both
        // 1. q = k ^{ 1/ epsilon}
        // 2. q = p ^{t} - 1, for some integers p, t.

        if(sec_level_ == 4){

        }else if (sec_level_ == 16){

        }else if (sec_level_ == 64){

        }else if (sec_level_ == 128){

        }

        // TODO:- is q here < 64 bit always?
        uint64_t q_min = pow(sec_level_, 1/epsilon);
        uint64_t q = NTL::NextPrime(q_min);
        cipher_modulus_ = q;
    }

    void EncryptionParameters::find_cgsw2_modulus(uint64_t sec_level, double rate) {
        auto epsilon = 1 - rate;
        // 1. gen q according to first equation
        auto q = pow(sec_level, 1 / epsilon);

        std::cout << "Sec: " << sec_level << ", Rate: " << rate << "->  q: " << q << std::endl;
    }

}
