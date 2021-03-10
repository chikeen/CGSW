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

    void Encryptor::encrypt_gsw(const Plaintext &plain, Ciphertext &destination) {
        encrypt_single_bit(plain.data(), destination);
    }

    void Encryptor::encrypt_cgsw(const CGSWPlaintext &plains, dddCipherMatrix &destination){
        for (auto i: plains.bit_decomposed_data()){
            ddCipherMatrix ciphertexts;
            encrypt_mat(i, ciphertexts);
            destination.push_back(ciphertexts);
        }
        // the iterate order is now: w(low bit -> high bit) -> u (up to down) -> v(left to right)

        return;
    }

    Ciphertext Encryptor::compress(const dddCipherMatrix &ciphertexts){
        CGSW_mat result;
        result.SetDims(params_.getLatticeDimension1(), params_.getLatticeDimension0());
        Ciphertext cresult;
        cresult.set_data(result);
        smart_compress(ciphertexts, cresult);
        return cresult;
    }


    //-------------- private -----------------------
    CGSW_mat Encryptor::generate_t_matrix(uint64_t scalar, int u, int v, size_t n1, size_t n0) {
        CGSW_mat t;
        t.SetDims(n1, n0);
        t[u + (n1 - n0)][v] = scalar;
        return t;
    }

    void Encryptor::normal_compress(const dddCipherMatrix &ciphertexts, Ciphertext &results) {

        // variables
        uint64_t f = params_.getF(),
                l = params_.getL(),
                n0 = params_.getLatticeDimension0(),
                n1 = params_.getLatticeDimension1();

        // original ciphertext dimensions are n1 x m,

        // create a final result
        CGSW_mat result;
        result.SetDims(n1, n0);

        // loop through u, v, w
        for(int w = 0; w < l ; w ++){
            // calculate the scalar f * 2^w
            uint64_t scalar = f * pow(2, w);

            for(int u = 0; u < n0; u ++){
                for(int v = 0; v < n0; v ++){

                    // construct the matrix t
                    CGSW_mat t = generate_t_matrix(scalar, u, v, n1, n0);

                    // multiply row v with t and add it to col u
                    CGSW_mat rhs;
                    util::bit_decompose_matrix(rhs, t, l);

                    result += ciphertexts[w][u][v].data() * rhs;
                }
            }
        }

        results.set_data(result);
    }

    void Encryptor::smart_compress(const dddCipherMatrix &ciphertexts, Ciphertext &results) {

        std::cout << "Called once" << std::endl;

        // variables
        uint64_t f = params_.getF(),
                l = params_.getL(),
                n0 = params_.getLatticeDimension0(),
                n1 = params_.getLatticeDimension1(),
                m = params_.getM();

        // create a final result
        CGSW_mat result = results.data();

        // original ciphertext dimensions are n1 x m, compressed ciphertext n1 x n0

        // loop through u, v, w
        for(int w = 0; w < l ; w ++){
            // calculate the scalar f * 2^w
            uint64_t scalar = f * pow(2, w);

            for(int u = 0; u < n0; u ++){ // rows
                for(int v = 0; v < n0; v ++){ // cols

                    // construct the vector t
                    CGSW_vec t = generate_t_vector(scalar, u, l, m);

                    // multiply row v with t and add it to col u
                    for (int u2 = 0 ; u2 < n1; u2 ++ ){
                        result[u2][v] += ciphertexts[w][u][v].data()[u2] * t;
                    }
                }
            }
        }

        results.set_data(result);
    }

    void Encryptor::encrypt_mat(const CGSW_mat_uint &plain, ddCipherMatrix &destination) {
        for (int i = 0; i < plain.NumRows(); i ++){
            std::vector<Ciphertext> ciphertexts_row;
            for (int j = 0; j < plain.NumCols(); j ++){
                Ciphertext c;
                encrypt_single_bit(plain[i][j], c);
                ciphertexts_row.push_back(c);
            }
            destination.push_back(ciphertexts_row);
        }
        // iterate order is: u(row) -> v(col)
        return;
    }

    void Encryptor::encrypt_single_bit(const uint64_t &input, Ciphertext &destination) {
        // generate random matrix of size (m x m) { 0, 1 }
        CGSW_mat r, C;

        util::gen_random_matrix(r,
                                params_.getM(),
                                params_.getM(),
                                2); // generate random binary matrix

        C = public_key_.data() * r + input * gadget_matrix_;

        // putting ciphertext in place
        destination.set_data(C);
    }

    inline CGSW_vec Encryptor::generate_t_vector(uint64_t scalar, uint64_t u, uint64_t l, uint64_t length){
        CGSW_vec result;
        result.SetLength(length);

        for(int i = 0; i < l; i++){
            result[(params_.getSecLevel() + u) * l + i] = bit(scalar, i); // secLevel = k rows on top
        }

        return result;
    }

}

