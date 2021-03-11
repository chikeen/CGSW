//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "../../include/cgsw/decryptor.h"


//dynMatrix powers_of_2(dynMatrix m, uint64_t l){
////    if (m.rows() != 1) return m; // only do column
//    dynMatrix ans = dynMatrix (1, m.cols()*l);
//    for (int i = 0; i < m.cols(); i++ ){
//        for (int j = 0; j < l; j++){
//            ans(0, i*l +j) = m(0, i) * pow(2, j);
//        }
//    }
//    return ans;
//}

namespace cgsw {

    Decryptor::Decryptor(const EncryptionParameters &params, const SecretKey &secret_key): params_(params), secret_key_(secret_key) {
        // Verify parameters
//        if (!context_.parameters_set()) // TODO:- check if i need parameters_set?
//        {
//            throw std::invalid_argument("encryption parameters are not set correctly");
//        }

        // generate gadget matrix
        util::gen_gadget_matrix(gadget_matrix_, params_.getLatticeDimension0(),
                                                      params_.getM());
    }

    void Decryptor::decrypt(const Ciphertext &encrypted, Plaintext &decrypted){

        auto m = params_.getM();
        CGSW_mat SC = secret_key_.sk() * encrypted.data();

//        std::cout << "SC: " << SC << std::endl;
//        std::cout << SC.NumCols() << " " << SC.NumRows() << std::endl;
//        std::cout << "SC sum():" << util::get_sum(SC) << std::endl;
//        std::cout << "threshold_1: " << m * q/8 * 3 << std::endl;
//        std::cout << "threshold_2: " << m * params_.getF()  << std::endl;

        // Round off each element to the nearest multiples of f = q/p
//        for (int i = 0; i < SC.size(); i++){
//            double divided = SC(0, i) / params_.getF();
//
//        }
//        divide -> average

//        decrypted.set_data(SC.norm() / n )

        if(util::get_sum(SC) < m * params_.getF()){
            decrypted.set_data( 0);
        }
        else{
            decrypted.set_data(1);
        }

        return;
    }


    void Decryptor::compressed_decrypt(const Ciphertext &encrypted, CGSWPlaintext &decrypted) {
        auto n0 = params_.getLatticeDimension0();
        auto q = params_.getCipherModulus();
        auto f = params_.getF();

        CGSW_mat SC = secret_key_.sk() * encrypted.data();

        // transform back to plaintext
        CGSW_mat_uint p_data;
        p_data.SetDims(n0, n0);
//        std::cout << "q: " << q << std::endl;
//        std::cout << "SC: " << SC << std::endl;
//        std::cout << "SC size: " << SC.NumRows() << " " << SC.NumCols() << std::endl;

        long tmp = 0;
        for (int i = 0; i < n0; i ++ ){
            for (int j = 0; j < n0; j ++ ){
                // TODO:- note that we are using CGSW_long to uint64 conversion here,
                // implying that all matrix element should be able to fit in 64 bit int ( no need ZZ)
                // or we can try implement a better round_division that supports ZZ
                NTL::conv(tmp, rep(SC[i][j])); // <- this conversion
                p_data[i][j] = util::round_division(tmp, f);
            }
        }

        decrypted.set_data(p_data);
        return;
    }

    int Decryptor::invariant_noise_budget(const Ciphertext &encrypted) {
        return 0;
    }



}