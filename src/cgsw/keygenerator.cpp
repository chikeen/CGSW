//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "keygenerator.h"
#include "utils/utils.h"


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
        matrixElemType q = params_.getCipherModulus();
        dynMatrix s, t;

        switch(params_.getScheme()){
            case scheme_type::gsw:
                s = util::gen_random_matrix(1, n0 - 1, q);
                t = util::gen_empty_matrix(1, n0);

                t << s, matrixElemType (1);
                break;

            case scheme_type::cgsw:
                s = util::gen_random_matrix(n0, k, q);
                t = util::gen_empty_matrix(n0, n1);

                t << s, util::gen_identity_matrix(n0);
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
        matrixElemType q = params_.getCipherModulus();

        dynMatrix e, B, b_, A;

        switch(params_.getScheme()){
            case scheme_type::gsw:
                // Generating error matrix (vector) 1 x M
                e = util::gen_normal_matrix(1, m, q);

                // Generating random matrix B (n x m)
                B = util::gen_random_matrix(n0 - 1, m, q);

                b_ = secret_key_.sv() * B + e;
                util::modulo_matrix(b_, q);
                A = util::gen_empty_matrix(n0, m);
                util::negate_matrix(B, q);
                break;

            case scheme_type::cgsw:
                // Generating error matrix n0 x M
                e = util::gen_normal_matrix(n0, m, q);

                // Generating random matrix B (k x m)
                B = util::gen_random_matrix(k, m, q);

                b_ = secret_key_.sv() * B + e;
                util::modulo_matrix(b_, q);
                A = util::gen_empty_matrix(n1, m);
                util::negate_matrix(B, q);
                break;
        }

        A << B, //-B
             b_;

        PublicKey pk = PublicKey();
        pk.pk_ = A;

        return pk;
    }
}
