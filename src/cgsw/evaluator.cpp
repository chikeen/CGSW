//
// Created by Chi Keen Tan on 17/12/2020.
//

#include "../../include/cgsw/evaluator.hpp"


namespace cgsw {

    Evaluator::Evaluator(const EncryptionParameters &params): params_(params){
    }

    void Evaluator::negate_inplace(Ciphertext &encrypted) {

    }

    void Evaluator::add_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2) {
        CGSW_mat result = encrypted1.data() + encrypted2.data();
        encrypted1.set_data(result);
    }

    void Evaluator::sub_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2){

    }

    void Evaluator::multiply_inplace(Ciphertext &encrypted1, const Ciphertext &encrypted2){
        uint64_t l = params_.getPL();

        CGSW_mat decomposed;
        util::bit_decompose_matrix(decomposed, encrypted2.data(), l);

        CGSW_mat result = encrypted1.data() * decomposed;
        encrypted1.set_data(result);
    }


    //cgsw1
    void Evaluator::add_inplace(CGSWCiphertext &encrypted1, const CGSWCiphertext &encrypted2) {
        CGSW_mat result = encrypted1.data() + encrypted2.data();
        encrypted1.set_data(result);
    }

    void Evaluator::sub_inplace(CGSWCiphertext &encrypted1, const CGSWCiphertext &encrypted2) {
        CGSW_mat result = encrypted1.data() - encrypted2.data();
        encrypted1.set_data(result);
    }

    void Evaluator::multiply_inplace_gsw(CGSWCiphertext &encrypted1, const GSWCiphertext &encrypted2) {
        CGSW_mat bd;
        util::bit_decompose_matrix(bd, encrypted1.data(), params_.getQL());
        encrypted1.set_data(encrypted2.data() * bd);
    }

    void Evaluator::multiply_inplace_plaintext(CGSWCiphertext &encrypted, const CGSWPlaintext){
        throw NotImplemented();
    }



}