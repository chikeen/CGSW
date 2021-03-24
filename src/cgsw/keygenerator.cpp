//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "../../include/cgsw/keygenerator.hpp"
#include "cgsw/utils/utils.hpp"


namespace cgsw {

    KeyGenerator::KeyGenerator(const EncryptionParameters &params) : params_(params) {

        // generate secret matrix/key
        generate_sk();
    }

    const SecretKey &KeyGenerator::secret_key() const {
        if (!sk_generated_) {
            throw std::logic_error("secret key has not been generated");
        }
        return secret_key_;
    }

    void KeyGenerator::generate_sk() {

        uint64_t n0 = params_.getLatticeDimension0();
        uint64_t n1 = params_.getLatticeDimension1();
        uint64_t k = params_.getSecLevel();
        CGSW_long q = params_.getCipherModulus();
        CGSW_mat s, t, i;


        switch(params_.getScheme()){
            case scheme_type::gsw:
                util::gen_random_matrix(s, 1, n0);
                util::gen_identity_matrix(i, 1, 1);
                util::concat_matrix_h(t, s, i);
                break;

            case scheme_type::cgsw1:
            case scheme_type::cgsw2:
                util::gen_random_matrix(s, n0, k);
                util::gen_identity_matrix(i, n0, n0);
                util::concat_matrix_h(t, s, i);
                break;
        }

        sk_generated_ = true;
        secret_key_ = SecretKey();
        secret_key_.sk_ = t;
        secret_key_.sv_ = s;
    }

    PublicKey KeyGenerator::generate_pk() {

//        if(!sk_generated_){
//            return; //TODO:- error
//        }

        uint64_t k = params_.getSecLevel();
        uint64_t n0 = params_.getLatticeDimension0();
        uint64_t n1 = params_.getLatticeDimension1();
        uint64_t m = params_.getM();
        CGSW_long q = params_.getCipherModulus();

        CGSW_mat e, B, b_, A;

        switch(params_.getScheme()){
            case scheme_type::gsw:
                // Generating error matrix (vector) 1 x M
                util::gen_normal_matrix(e, 1, m);

                // Generating random matrix B (n x m)
                util::gen_random_matrix(B, n0, m);

                b_ = secret_key_.sv() * B + e;
                B = -B; // OPT:: Can negate at gen_random_matrix;
                break;

            case scheme_type::cgsw1:
            case scheme_type::cgsw2:
                // Generating error matrix n0 x M
                util::gen_normal_matrix(e, n0, m);

                // Generating random matrix B (k x m)
                util::gen_random_matrix(B, k, m);

                b_ = secret_key_.sv() * B + e;
                B = -B;
                break;
        }

        util::concat_matrix_v(A, B, b_);

        PublicKey pk = PublicKey();
        pk.pk_ = A;

        return pk;
    }
}
