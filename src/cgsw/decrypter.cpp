//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "../../include/cgsw/decrypter.hpp"


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

    Decrypter::Decrypter(const EncryptionParameters &params, const SecretKey &secret_key): params_(params), secret_key_(secret_key) {

        // generate gadget matrix
        util::gen_g_gadget_matrix(gadget_matrix_, params_.getLatticeDimension0(),
                                  params_.getM());
    }

    void Decrypter::decrypt(const Ciphertext &encrypted, GSWPlaintext &decrypted){

        auto m = params_.getM();
        CGSW_mat SC = secret_key_.sk() * encrypted.data();

        if(util::get_sum(SC) < m * params_.getF()){
            decrypted.set_data( 0);
        }
        else{
            decrypted.set_data(1);
        }
    }


    void Decrypter::compressed_decrypt(const Ciphertext &encrypted, CGSWPlaintext &decrypted) {
       if(params_.getScheme() == scheme_type::cgsw1){
           compressed_decrypt_cgsw1(encrypted, decrypted);
       } else if (params_.getScheme() == scheme_type::cgsw2){
           compressed_decrypt_cgsw2(encrypted, decrypted);
       }
    }

    int Decrypter::invariant_noise_budget(const Ciphertext &encrypted) {
        return 0;
    }


    /// Private:

    void Decrypter::compressed_decrypt_cgsw1(const Ciphertext &encrypted, CGSWPlaintext &decrypted) {
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
    }

    void Decrypter::compressed_decrypt_cgsw2(const Ciphertext &encrypted, CGSWPlaintext &decrypted) {
        auto n0 = params_.getLatticeDimension0();
        auto f = params_.getF();

        // 0. X := SC = MH + E
        CGSW_mat SC = secret_key_.sk() * encrypted.data();

        // 1. XF = SCF = MHF + EF = EF  - rmb HF = 0
        // TODO:- where to get H?
        CGSW_mat EF = SC * params_.getFTrapdoorMat();
        // since we have no error this should be zero

        // 2. TODO:- EF x F-1 = E ( or somehow calculate E using the fact that F has full rank over the reals)
        CGSW_mat E;

        // 3. SC - E =  MH
        CGSW_mat MH = SC - E;

        // 4. TODO:- somehow recover M from MH using the fact that H has rank n0 modulo q.
        CGSW_mat M;

        // 5. transform back to plaintext data
        CGSW_mat_uint p_data;
        p_data.SetDims(n0, n0);

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
    }
}