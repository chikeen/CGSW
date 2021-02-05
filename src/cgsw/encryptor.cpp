//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "encryptor.h"



namespace cgsw{

    Encryptor::Encryptor(const EncryptionParameters &params, const PublicKey &public_key) : params_(params)
    {

        set_public_key(public_key);

        // generate gadget matrix
        gadget_matrix_ = util::gen_gadget_matrix(params_.getLatticeDimension(),
                                                      params_.getM());
    }

    void Encryptor::encrypt(const Plaintext &plain, Ciphertext &destination) {
        // generate random matrix of size (m x m) { 0, 1 }
        dynMatrix r = util::gen_random_matrix(params_.getM(),
                                                   params_.getM(),
                                                   matrixElemType (2));

        dynMatrix C = public_key_.data() * r + plain.data() * gadget_matrix_;
        C = util::modulo_matrix(C, params_.getCipherModulus());

        // putting ciphertext in place
        Ciphertext ciphertext = Ciphertext();
        ciphertext.set_data(C);
        destination = ciphertext;

        return;
    }

    void Encryptor::encrypt_many(const dynUintMatrix &plains, std::vector<Ciphertext> &destination) {
        for (int i = 0; i < plains.rows(); i ++){
            for (int j = 0; j < plains.cols(); j ++){
                Ciphertext c;
                Plaintext p(plains(i, j));
                encrypt(p, c);
                destination.push_back(c);
            }
        }

        return;
    }

    void Encryptor::encrypt_many(const std::vector<dynUintMatrix> &plains, std::vector<std::vector<Ciphertext>> &destination){
        for (auto i: plains){
            std::vector<Ciphertext> ciphertexts;
            encrypt_many(i, ciphertexts);
            destination.push_back(ciphertexts);
        }

        return;
    }

    void Encryptor::compress(const std::vector<Ciphertext> &ciphertexts, Ciphertext &results) {


        // construct T' matrix


        //
    }


    dynUintMatrix Encryptor::construct_T_prime_matrix() {

    }

}

