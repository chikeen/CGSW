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

    Decryptor::Decryptor(const CGSWContext &context, const SecretKey &secret_key): context_(context), secret_key_(secret_key) {
        // Verify parameters
//        if (!context_.parameters_set()) // TODO:- check if i need parameters_set?
//        {
//            throw std::invalid_argument("encryption parameters are not set correctly");
//        }

        // generate gadget matrix
        gadget_matrix_ = util::gen_gadget_matrix(context_.parms().getLatticeDimension(),
                                                      context_.parms().getM());
    }

    void Decryptor::decrypt(const Ciphertext &encrypted, Plaintext &decrypted){


//      PowersOf2
        uint64_t l = context_.parms().getL();
        uint64_t q = context_.parms().getModulus();



        dynMatrix SC = secret_key_.sk() * encrypted.data();
        util::modulo_matrix(SC, q);

        std::cout << "SC: "<< std::endl << SC << std::endl;

        dynMatrix SG = secret_key_.sk() * gadget_matrix_;
        util::modulo_matrix(SG, q);

        std::cout << "SG: "<< std::endl << SG << std::endl;

        dynMatrix div = dynMatrix (SC.rows(), SC.cols());

        for(int i = 0; i < div.cols(); i++){
//            div(0, i) = (SC(0, i) < SG(0, i)/2)? 0 : 1;
            // handle division by zero
            if(SG(0, 1) == 0)
                div(0, i) = q;
            else
                div(0, i) = (SC(0, i) / SG(0, i));
        }

        std::cout << "DIV: " << std::endl << div << std::endl;
        std::cout << "sum DIV: " << div.sum() << std::endl;


        decrypted.set_data(1);


//        dynMatrix v = powers_of_2(secret_key_.sk(),l);
//
//        util::modulo_matrix(v, q);
//
//        std::cout << "s: " << secret_key_.sk() << std::endl;
//        std::cout << "v: " << v << std::endl;


//        // Find i so that q/4 < w_i < q/2
//        int index;
//        for (int i = 0; i < v.cols(); i ++){
//            if ((v(0, i) > q/4 ) && (v(0, i) < q/2)){
//                index = i;
//                break;
//            }
//        }
//
//        dynMatrix element = encrypted.data().row(index);
//
//        dynMatrix ans = element * v.transpose() ;
//
//        std::cout << "index, i = " << index << std::endl;
//        std::cout <<"element = " << element << std::endl;
//        std::cout <<"answer = " << ans << std::endl;
//        std::cout << "final anwer = " << (ans(0, 0)/v(0, index)) % q << std::endl;


//        dynMatrix w = secret_key_.sk() * encrypted.data();
//        w = w.unaryExpr([&](const int x) { return x % context_.parms().getModulus(); });
//
////        dynMatrix z = secret_key_.sk() * gadget_matrix_;
////        z = z.unaryExpr([&](const int x) { return x % context_.parms().getModulus(); });
//
////        dynMatrix a = w.colPivHouseholderQr().solve(z);
//        uint64_t q_4 = context_.parms().getModulus()/2;
//        std::cout << "w: " << w << std::endl;
//        w = w.unaryExpr([&](const int x) { if ( x < q_4) {return (uint64_t ) 0;} else return (uint64_t ) 1; });
//
//        std::cout << std::endl;
//        std::cout << "ans: " << w << std::endl;
//        std::cout << "ans mean: " << w.sum()<< std::endl;
//        std::cout << "final answer: " << v(0, context_.parms().getM()-1) >= context_.parms().getModulus()/4? 1 :0 << std::endl;
//        std::cout << "z: " << z << std::endl;
//
//        v = v.unaryExpr([&](const int x) { return x % context_.parms().getModulus(); });

//----------------

//        dynMatrix msg = secret_key_.sk() * encrypted.data();
//        // modulo it
//        msg = msg.unaryExpr([&](const int x) { return x % context_.parms().getModulus(); });
//
//        dynMatrix sg = secret_key_.sk() * gadget_matrix_;
//        //modulo it
//        sg = sg.unaryExpr([&](const int x) { return x % context_.parms().getModulus(); });
//
//        // coefficient-wise division
//        dynMatrix diw = dynMatrix(msg.rows(), msg.cols());
//        for(int i = 0; i < msg.rows(); i ++){
//            for(int j = 0; j < msg.cols(); j ++) {
//                if (sg(i, j) != 0)
//                    div(i, j) = (msg(i, j) / sg(i, j)) % context_.parms().getModulus();
//                else
//                    div(i, j) = (msg(i, j) / context_.parms().getModulus()) % context_.parms().getModulus();
//            }
//        }
//
//        std::cout << "gad" << std::endl;
//        std::cout << gadget_matrix_ << std::endl;
//
//        std::cout << "sc" << std::endl;
//        std::cout << secret_key_.sk() << std::endl;
//
//        std::cout << "msg" << std::endl;
//        std::cout << msg << std::endl;
//
//        std::cout << "sg" << std::endl;
//        std::cout << sg << std::endl;
//
//        std::cout << "div" << std::endl;
//        std::cout << div << std::endl;
//
//        std::cout << "div mean: " << div.mean() << std::endl;
//
//        // ideally every index in this new array should contains the message, m. To isolate the correct value m
//        // we take each unique value in div and multiply by sg. We then compute the distance d = ||div * sg - msg||
//        // for every unique value in r. the correct m will have the smallest distance d, so this is the value to
//        // decrypt to
//        std::vector<std::pair<uint64_t, uint64_t>> modes;
//        uint64_t tmp_count;
//        dynMatrix dist(1, msg.cols());
//        int best_num = 0;
//        int best_dist = INFINITY;
//
//        for (int i = 0; i < context_.parms().getModulus() ; i ++ ) {
//            tmp_count = (div.array() > 0).count();
//            if (tmp_count != 0) {
//                modes.push_back(std::make_pair(i, tmp_count));
//
//                dist = (msg - i * sg);
//                dist = dist.unaryExpr([&](const int x) { return x % context_.parms().getModulus(); });
//
//                int tmp_dist = 0;
//                // return element wise minimum
//                for (int j = 0; j < dist.cols(); j ++){
//                    if (dist(0, j) > context_.parms().getModulus()/2){
//                        dist(0, j) = context_.parms().getModulus() - dist(0, j);
//                    }
//
//                    tmp_dist += pow(dist(0, j), 2);
//                }
//
//                if (tmp_dist < best_dist){
//                    best_num = i;
//                    best_dist = tmp_dist;
//                }
//            }
//        }
//
//
//        std::cout << "ha, your secret message is: " << best_num << "with best_dist: " << best_dist << std::endl;

        return;
    }

    int Decryptor::invariant_noise_budget(const Ciphertext &encrypted) {
        return 0;
    }



}