//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "encryptor.h"



namespace cgsw{

    Encryptor::Encryptor(const CGSWContext &context, const PublicKey &public_key) : context_(context)
    {
        // Verify parameters
//        if (!context_.parameters_set()) // TODO:- check if i need parameters_set?
//        {
//            throw std::invalid_argument("encryption parameters are not set correctly");
//        }

        set_public_key(public_key);

        // generate gadget matrix
        gadget_matrix_ = util::gen_gadget_matrix(context_.parms().getLatticeDimension(),
                                                      context_.parms().getM());
    }

    void Encryptor::encrypt(Plaintext &plain, Ciphertext &destination) {
        // generate random matrix of size (m x m) { 0, 1 }
        dynMatrix r = util::gen_random_matrix(context_.parms().getM(),
                                                   context_.parms().getM(),
                                                   2);

        // we are not using plaintext here: 7 is our message straightaway
        dynMatrix C = public_key_.data() * r + plain.data() * gadget_matrix_;
        C = C.unaryExpr([&](const int x) { return x % context_.parms().getModulus(); }); // modulo

        // putting ciphertext in place
        Ciphertext ciphertext = Ciphertext();
        ciphertext.set_data(C);
        destination = ciphertext;

//        std::cout << C << std::endl;

        return;

    }

}

