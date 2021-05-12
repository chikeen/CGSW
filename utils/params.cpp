//
// Created by Chi Keen Tan on 24/04/2021.
//


#include <fstream>
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;


void print_cgsw1_params_table(){
    // print_cgsw_table for 1:10

    EncryptionParameters params(scheme_type::cgsw1);

    std::ofstream file("cgsw1_params_file.csv");

    file << "CGSW1 EncryptionParams table\n";
    file << "\n";

    file << "k, rate, p, q, n0, n1, n2, m, l_p, l_q, f_, lhs, rhs\n";

    for (int k = 1; k < 3; k ++){

        for (int rate = 1; rate < 3; rate ++){
            file << k << ",";
            file << rate * 0.1<< ",";

            params.set_security_level(k);
            params.set_rate(rate * 0.2);
            params.compute();

            file << params.getPlainModulus() << ",";
            file << params.getCipherModulus() << ",";
            file << params.getLatticeDimension0() << ",";
            file << params.getLatticeDimension1() << ",";
            file << params.getLatticeDimension2() << ",";
            file << params.getM() << ",";
            file << params.getPL() << ",";
            file << params.getQL() << ",";
            file << params.getF() << ",";

            auto alpha = 1; //noise of GSW fresh-ciphertext
            auto epsilon = 1 - rate;
            auto lhs =  power(params.getPlainModulus(), 0.5 * epsilon)/2;
            auto rhs = alpha * pow(params.getM(), 3)
                       * pow(params.getLatticeDimension0(), 2)
                       * log2(params.getP());

            file << lhs << "," << rhs <<",";

            if (lhs > rhs)
                file << "pass \n";
            else
                file << "fail \n";
        }
    }

    file.close();
}


int main(){

    print_cgsw1_params_table();
    return 0;
}
