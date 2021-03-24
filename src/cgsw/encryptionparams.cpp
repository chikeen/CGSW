//
// Created by Chi Keen Tan on 16/12/2020.
//


#include "../../include/cgsw/encryptionparams.hpp"
#include "../../include/cgsw/utils/numth.hpp"
#include <cmath>
#include <cstdint>


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

    uint64_t EncryptionParameters::getR() const {
        return r_;
    }

    uint64_t EncryptionParameters::getT() const {
        return t_;
    }

    uint64_t EncryptionParameters::getP() const {
        return p_;
    }

    scheme_type EncryptionParameters::getScheme() const {
        return scheme_;
    }

    double EncryptionParameters::getRate() const {
        return rate_;
    }

    CGSW_mat EncryptionParameters::getGGadgetMat() const {
        return g_mat_;
    }

    CGSW_mat EncryptionParameters::getHGadgetMat() const {
        return h_mat_;
    }

    CGSW_mat EncryptionParameters::getFTrapdoorMat() const {
        return f_mat_;
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
                os << "|   l_q: " << parms.getQL() << std::endl;
                os << "|   f: " << parms.getF() << std::endl;
                os << "\\" << std::endl;
                break;
            case scheme_type::cgsw2:
                scheme_name = "CGSW, Nearly square variant";
                os << "/" << std::endl;
                os << "| Encryption parameters :" << std::endl;
                os << "|   scheme: " << scheme_name << std::endl;
                os << "|   security level (k): " << parms.getSecLevel() << std::endl;
                os << "|   depth (d): " << parms.getDepth() << std::endl;
                os << "|   rate (1-epsilon): " << parms.getRate() << std::endl;
                os << "|   ciphertext modulus (q): " << parms.getCipherModulus() << std::endl;
                os << "|   lattice dimension (n0, n1, n2): " <<
                        parms.getLatticeDimension0() << ", " <<
                        parms.getLatticeDimension1() << ", " <<
                        parms.getLatticeDimension2() << std::endl;
                os << "|   second lattice dimension (m): " << parms.getM() << std::endl;
                os << "|   l_q: " << parms.getQL() << std::endl;
                os << "|   r: " << parms.getR() << std::endl;
                os << "|   t: " << parms.getT() << std::endl;
                os << "|   p: " << parms.getP() << std::endl;
                os << "|   f_mat_: \n" << parms.getFTrapdoorMat() << std::endl;
                os << "|   h_mat_: \n" << parms.getHGadgetMat() << std::endl;

                os << "\\" << std::endl;
                break;
            default:
                break;
        }

        return os;
    }


    /// Private:

    void EncryptionParameters::set_cgsw_modulus() {

        auto epsilon = 1 - rate_;
        uint64_t p_min = pow(sec_level_, 5/epsilon);
        uint64_t p = NTL::NextPrime(p_min);

        uint64_t q_min = pow(p, 5 + epsilon/2);
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

        util::gen_g_gadget_matrix(g_mat_, lattice_dimension_1_, m_);

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

        util::gen_g_gadget_matrix(g_mat_, lattice_dimension_1_, m_);
    }

    void EncryptionParameters::compute_cgsw2_params() {
        sec_level_ = 1;

        // TODO:- Not sure how to set q and the followings at the moment
        cipher_modulus_ = 3;
        p_ = 2;
        t_ = 2;

        // those are derived
        CGSW_mod::init(cipher_modulus_);
        plain_modulus_ = cipher_modulus_;
        r_ = t_;
        lattice_dimension_0_ = r_ * (t_ - 1);
        lattice_dimension_1_ = lattice_dimension_0_ + sec_level_;
        lattice_dimension_2_ = r_ * t_;
        l_q_ = ceil(log2(cipher_modulus_));
        l_p_ = ceil(log2(plain_modulus_));
        m_ = lattice_dimension_1_ * l_q_;

        // constructing gadget matrix
        CGSW_mat f_tmp, h_tmp;
        util::gen_g_gadget_matrix(g_mat_, lattice_dimension_1_, m_);
        util::gen_f_trapdoor_matrix(f_tmp, p_, t_);
        util::gen_h_gadget_matrix(h_tmp, t_);
        f_mat_ = f_tmp;
        h_mat_ = h_tmp;

        // n0 = r (t - 1)
        // n1 = n0 + k <= n0/ (1 - epsilon/2)
        // n2 = rt <= n0/( 1- epsilon/2)
        // from a map of params (sec_level_, rate_ ) => (q, r, t)

    }

    void EncryptionParameters::find_cgsw2_modulus(uint64_t sec_level, double rate) {
        // cipher modulus are chosen from a list of predifined options that satisfied both
        // 1. q = k ^{ 1/ epsilon}
        // 2. q = p ^{t} - 1, for some integers p, t.
        auto epsilon = 1 - rate;
        // 1. gen q according to first equation
        auto q = pow(sec_level, 1 / epsilon);

        // TODO:- is q here < 64 bit always?
//        uint64_t q_min = pow(sec_level_, 1/epsilon);
//        uint64_t q = NTL::NextPrime(q_min);

        // TODO:- not sure how exactly are the configuration gonna be done here
        // TEMP:- fix
        cipher_modulus_ = 5;
        CGSW_mod::init(cipher_modulus_);

//        std::cout << "Sec: " << sec_level << ", Rate: " << rate << "->  q: " << q << std::endl;
    }

}
