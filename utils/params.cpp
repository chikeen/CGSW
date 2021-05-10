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

    file << "k, rate, p, q, n0, n1, n2, m, l_p, l_q, f_ \n";

    for (int k = 1; k < 10; k ++){

        for (int rate = 1; rate < 5; rate ++){
            file << k << ",";
            file << rate * 0.2 << ",";

            try {
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
                file << params.getF() << "\n";

            } catch (...) {
            }

        }
    }

    file.close();
}


int main(){

    print_cgsw1_params_table();
    return 0;
}
