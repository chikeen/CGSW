//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "../../include/cgsw/encryptor.h"



namespace cgsw{

    Encryptor::Encryptor(const EncryptionParameters &params, const PublicKey &public_key) : params_(params)
    {

        set_public_key(public_key);

        // generate gadget matrix
        util::gen_gadget_matrix(gadget_matrix_, params_.getLatticeDimension1(),
                                                      params_.getM());
    }

    void Encryptor::encrypt(const Plaintext &plain, Ciphertext &destination) {
        // generate random matrix of size (m x m) { 0, 1 }
        CGSW_mat r, C;

        util::gen_random_binary_matrix(r,
                                       params_.getM(),
                                       params_.getM());

        C = public_key_.data() * r + plain.data() * gadget_matrix_;

        // putting ciphertext in place
        destination.set_data(C);
    }

    void Encryptor::encrypt_many(const CGSW_mat_uint &plains, ddCipherMatrix &destination) {
        for (int i = 0; i < plains.NumRows(); i ++){
            std::vector<Ciphertext> ciphertexts;
            for (int j = 0; j < plains.NumCols(); j ++){
                Ciphertext c;
                Plaintext p(plains(i, j));
                encrypt(p, c);
                ciphertexts.push_back(c);
            }
            destination.push_back(ciphertexts);
        }
        // iterate order is: u(row) -> v(col)

        return;
    }

    void Encryptor::encrypt_many(const std::vector<CGSW_mat_uint> &plains, dddCipherMatrix &destination){
        for (auto i: plains){
            ddCipherMatrix ciphertexts;
            encrypt_many(i, ciphertexts);
            destination.push_back(ciphertexts);
        }
        // the iterate order is now: w(low bit -> high bit) -> u (up to down) -> v(left to right)

        return;
    }

    void Encryptor::compress(const dddCipherMatrix &ciphertexts, Ciphertext &results) {

        // variables
        uint64_t rows = params_.getM(),
                 cols = params_.getM(),
                 f = params_.getF(),
                 l = params_.getL();

        // sizes
        uint64_t no_w = ciphertexts.size(),
                 no_u = ciphertexts[0].size(),
                 no_v = ciphertexts[0][0].size(),
                 t_size = ciphertexts[0][0][0].data().NumCols();

        // create a final result
        CGSW_mat result = results.data();

        // loop through u, v, w
        for(int w = 0; w < no_w ; w ++){
            // calculate the scalar f * 2^w
            uint64_t scalar = f * pow(2, w);

            for(int u = 0; u < no_u; u ++){ // cols
                for(int v = 0; v < no_v; v ++){ // rows

                    // construct the vector t
                    CGSW_vec t = generate_t_vector(scalar, v, l, t_size);
//                    std::cout << "t   : " << t.transpose()  << std::endl;
//                    std::cout << "rows: " << ciphertexts[w][u][v].data().row(v) << std::endl;

                    // multiply row v with t and add it to col u
                    result(u, v) += ciphertexts[w][u][v].data()[v] * t;
                }
            }
        }

        results.set_data(result);
        return;
    }

    Ciphertext Encryptor::compress(const dddCipherMatrix &ciphertexts){
        uint64_t rows = ciphertexts[0][0][0].data().NumRows(),
                 cols = ciphertexts[0][0][0].data().NumCols();

        CGSW_mat result;
        util::gen_empty_matrix(result, rows, cols);
        Ciphertext cresult;
        cresult.set_data(result);
        compress(ciphertexts, cresult);
        return cresult;
    }

    inline CGSW_vec Encryptor::generate_t_vector(uint64_t scalar, uint64_t v, uint64_t l, uint64_t length){
        CGSW_vec result;
        result.SetLength(length);

        for(int i = 0; i < length; i++){
            if((i >= v)  && (i < v + l)) {
                result(i) = (bit(scalar, i - v)); // current_l = i - v
            }
            else{
                result(i) = 0;
            }
        }

        return result;
    }




}

