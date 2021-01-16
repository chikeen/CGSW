//
// Created by Chi Keen Tan on 17/12/2020.
//

#include "evaluator.h"


namespace cgsw {

    Evaluator::Evaluator(const CGSWContext &context): context_(context){
    }

    void Evaluator::negate_inplace(Ciphertext &encrypted) {

    }

    void Evaluator::add_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2) {
        dynMatrix result = encrypted1.data() * encrypted2.data();
        util::modulo_matrix(result, context_.parms().getModulus());
        encrypted1.set_data(result);
    }

    void Evaluator::add_many(const std::vector<Ciphertext> &encrypteds, Ciphertext &destination) {

    }

    void Evaluator::sub_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2){

    }

    void Evaluator::multiply_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2){
        uint64_t q = context_.parms().getModulus();

        dynMatrix result = encrypted1.data() * util::bit_decompose_matrix(encrypted2.data(),q);
        encrypted1.set_data(result);
    }


}