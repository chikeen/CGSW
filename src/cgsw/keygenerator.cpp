//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "keygenerator.h"
#include "utils/utils.h"


namespace cgsw {

    KeyGenerator::KeyGenerator(const cgsw::CGSWContext &context) : context_(context) {
        //initialize matrix generator
        matrix_gen_ = util::MatrixGenerator();

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

        uint64_t n = context_.parms().getLatticeDimension();
        uint64_t m = context_.parms().getM();
        uint64_t q = context_.parms().getModulus();

        dynMatrix s = matrix_gen_.gen_random_matrix(1, n - 1, q);
        dynMatrix t = matrix_gen_.gen_empty_matrix(1, n);

        // negate s
        util::negate_matrix(s, q);
        t << s, 1;

        sk_generated_ = true;
        secret_key_ = SecretKey();
        secret_key_.sk_ = t;
        secret_key_.sv_ = s;
//        std::cout<< "secret key generated: "<< secret_key_.sk() <<std::endl;
    }

    PublicKey KeyGenerator::generate_pk() {

        if(!sk_generated_){
//            return; //TODO:- error
        }

        uint64_t n = context_.parms().getLatticeDimension();
        uint64_t m = context_.parms().getM();
        uint64_t q = context_.parms().getModulus();

        // Generating error matrix (vector) 1 x M
        dynMatrix e = matrix_gen_.gen_normal_matrix(1, m , q);

        // Generating random matrix B (n x m)
        dynMatrix B = matrix_gen_.gen_random_matrix(n - 1, m, q);

        dynMatrix b_ = secret_key_.sv() * B + e;
        util::modulo_matrix(b_, q);
        dynMatrix A = matrix_gen_.gen_empty_matrix(n, m);

        A << B, b_;

        PublicKey pk = PublicKey();
        pk.pk_ = A;

        return pk;
    }
}
