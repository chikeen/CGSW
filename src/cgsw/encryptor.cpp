//
// Created by Chi Keen Tan on 16/12/2020.
//

#include "encryptor.h"



namespace cgsw{

    Encryptor::Encryptor(const EncryptionParameters &params, const PublicKey &public_key) : params_(params)
    {

        set_public_key(public_key);

        // generate gadget matrix
        gadget_matrix_ = util::gen_gadget_matrix(params_.getLatticeDimension0(),
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

    void Encryptor::encrypt_many(const dynUintMatrix &plains, ddCipherMatrix &destination) {
        for (int i = 0; i < plains.rows(); i ++){
            std::vector<Ciphertext> ciphertexts;
            for (int j = 0; j < plains.cols(); j ++){
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

    void Encryptor::encrypt_many(const std::vector<dynUintMatrix> &plains, dddCipherMatrix &destination){
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
                 t_size = ciphertexts[0][0][0].data().cols();

        // create a final result
        dynMatrix result = results.data();

        // loop through u, v, w
        for(int w = 0; w < no_w ; w ++){
            // calculate the scalar f * 2^w
            uint64_t scalar = f * pow(2, w);

            for(int u = 0; u < no_u; u ++){ // cols
                for(int v = 0; v < no_v; v ++){ // rows

                    // construct the vector t
                    dynVector t = generate_t_vector(scalar, v, l, t_size);
                    std::cout << "t   : " << t.transpose()  << std::endl;
                    std::cout << "rows: " << ciphertexts[w][u][v].data().row(v) << std::endl;

                    // multiply row v with t and add it to col u
                    result(u, v) += ciphertexts[w][u][v].data().row(v) * t;
                }
            }
        }

        results.set_data(result);
        return;
    }

    Ciphertext Encryptor::compress(const dddCipherMatrix &ciphertexts){
        uint64_t rows = ciphertexts[0][0][0].data().rows(),
                 cols = ciphertexts[0][0][0].data().cols();

        dynMatrix result = dynMatrix::Zero(rows, cols);
        Ciphertext cresult;
        cresult.set_data(result);
        compress(ciphertexts, cresult);
        return cresult;
    }

    inline dynVector Encryptor::generate_t_vector(uint64_t scalar, uint64_t v, uint64_t l, uint64_t length){
        dynVector result(length);

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

