//
// Created by Chi Keen Tan on 17/12/2020.
//

#include "../../include/cgsw/evaluator.h"


namespace cgsw {

    Evaluator::Evaluator(const EncryptionParameters &params): params_(params){
    }

    void Evaluator::negate_inplace(Ciphertext &encrypted) {

    }

    void Evaluator::add_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2) {
        CGSW_mat result = encrypted1.data() + encrypted2.data();
        encrypted1.set_data(result);
    }

    void Evaluator::add_many(const std::vector<Ciphertext> &encrypteds, Ciphertext &destination) {

    }

    void Evaluator::sub_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2){

    }

    void Evaluator::multiply_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2){
        uint64_t l = params_.getL();

        CGSW_mat decomposed;
        util::bit_decompose_matrix(decomposed, encrypted2.data(), l);

        CGSW_mat result = encrypted1.data() * decomposed;
        encrypted1.set_data(result);
    }
}