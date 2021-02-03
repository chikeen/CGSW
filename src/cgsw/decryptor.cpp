//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "decryptor.h"


dynMatrix powers_of_2(dynMatrix m, uint64_t l){
//    if (m.rows() != 1) return m; // only do column
    dynMatrix ans = dynMatrix (1, m.cols()*l);
    for (int i = 0; i < m.cols(); i++ ){
        for (int j = 0; j < l; j++){
            ans(0, i*l +j) = m(0, i) * pow(2, j);
        }
    }
    return ans;
}


namespace cgsw {

    Decryptor::Decryptor(const EncryptionParameters &params, const SecretKey &secret_key): params_(params), secret_key_(secret_key) {
        // Verify parameters
//        if (!context_.parameters_set()) // TODO:- check if i need parameters_set?
//        {
//            throw std::invalid_argument("encryption parameters are not set correctly");
//        }

        // generate gadget matrix
        gadget_matrix_ = util::gen_gadget_matrix(params_.getLatticeDimension(),
                                                      params_.getM());
    }

    void Decryptor::decrypt(const Ciphertext &encrypted, Plaintext &decrypted){

        uint64_t l = params_.getL();
        uint64_t n = params_.getLatticeDimension();
        matrixElemType q = params_.getModulus();

        dynMatrix SC = secret_key_.sk() * encrypted.data();
        util::modulo_matrix(SC, q);

//        std::cout << "q: " << q << std::endl;
//        std::cout << "SC: " << SC << std::endl;
//        std::cout << "SC norm():" << SC.norm() << std::endl;
//        std::cout << "threshold: " << n * q/8 * 3 << std::endl;

        if(SC.norm() < n * q/8 * 3){
            decrypted.set_data(matrixElemType (0));
        }
        else{
            decrypted.set_data(matrixElemType (1));
        }

        return;
    }

    int Decryptor::invariant_noise_budget(const Ciphertext &encrypted) {
        return 0;
    }



}