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

    void Encryptor::encrypt(Plaintext &plain, Ciphertext &destination) {
        // generate random matrix of size (m x m) { 0, 1 }
        dynMatrix r = util::gen_random_matrix(params_.getM(),
                                                   params_.getM(),
                                                   matrixElemType (2));

        // we are not using plaintext here: 7 is our message straightaway
        dynMatrix C = public_key_.data() * r + plain.data() * gadget_matrix_;
        C = util::modulo_matrix(C, params_.getModulus());

        // putting ciphertext in place
        Ciphertext ciphertext = Ciphertext();
        ciphertext.set_data(C);
        destination = ciphertext;

//        std::cout << C << std::endl;

        return;

    }

}

