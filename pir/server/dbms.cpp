//
// Created by Chi Keen Tan on 10/05/2021.
//


/*
 * 1. read csv
 * 2. prepare database
 * 3.
 */


#include <iostream>
#include <fstream>
#include <sstream>
#include <cgsw/cgsw.hpp>


using namespace cgsw;
using namespace std;

// Utility functions to read <K,V> CSV data from file

std::vector<std::pair<int, int>> read_csv_int_int(std::string filename){
    std::vector<std::pair<int, int>> dataset;
    std::ifstream data_file(filename);

    if (!data_file.is_open())
        throw std::runtime_error(
                "Error: This example failed trying to open the data file: " + filename +
                "\n           Please check this file exists and try again.");

    std::vector<std::string> row;
    std::string line, entry, temp;

    if (data_file.good()) {
        // Read each line of file
        while (std::getline(data_file, line)) {
            row.clear();
            std::stringstream ss(line);
            while (getline(ss, entry, ',')) {
                row.push_back(entry);
            }
            // Add key value pairs to dataset
            dataset.push_back(std::make_pair(std::stoi(row[0]), std::stoi(row[1])));
        }
    }

    data_file.close();
    return dataset;
}

std::vector<std::pair<std::string, std::string>> read_csv_str_str(std::string filename){
    std::vector<std::pair<std::string, std::string>> dataset;
    std::ifstream data_file(filename);

    if (!data_file.is_open())
        throw std::runtime_error(
                "Error: This example failed trying to open the data file: " + filename +
                "\n           Please check this file exists and try again.");

    std::vector<std::string> row;
    std::string line, entry, temp;

    if (data_file.good()) {
        // Read each line of file
        while (std::getline(data_file, line)) {
            row.clear();
            std::stringstream ss(line);
            while (getline(ss, entry, ',')) {
                row.push_back(entry);
            }
            // Add key value pairs to dataset
            dataset.push_back(std::make_pair(row[0], row[1]));
        }
    }

    data_file.close();
    return dataset;
}




int main(int argc, char* argv[]){

    /************ CGSW boiler plate ************/

    // Note: The parameters have been chosen to provide a somewhat
    // faster running time with a non-realistic security level.
    // Do Not use these parameters in real applications.

    auto rate = 0.1;
    auto k = 2;

    std::string db_filename = "./data/simplest_int.csv";
    bool debug = false;

    std::cout << "\n*********************************************************";
    std::cout << "\n*           Privacy Preserving Search Example           *";
    std::cout << "\n*           =================================           *";
    std::cout << "\n*                                                       *";
    std::cout << "\n* This is a sample program for education purposes only. *";
    std::cout << "\n* It implements a very simple homomorphic encryption    *";
    std::cout << "\n* based db search algorithm for demonstration purposes. *";
    std::cout << "\n*                                                       *";
    std::cout << "\n*********************************************************";
    std::cout << "\n" << std::endl;

    std::cout << "---Initialising HE Environment ...\n ";
    // Initialize context
    // This object will hold information about the algebra used for this scheme.
    std::cout << "Initializing the Context ...\n";

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_rate(rate);
    params.set_security_level(k);
    params.compute();

    if (debug) std::cout << params << std::endl;

    /************ Read in the database ************/
    std::vector<std::pair<int, int>> simplest_db;
    try {
        simplest_db = read_csv_int_int(db_filename);
    } catch (std::runtime_error& e) {
        std::cerr << "\n" << e.what() << std::endl;
        exit(1);
    }

//    std::vector<std::pair<std::string, std::string>> country_db;
//    try {
//        country_db = read_csv_str_str(db_filename);
//    } catch (std::runtime_error& e) {
//        std::cerr << "\n" << e.what() << std::endl;
//        exit(1);
//    }

    for(int i = 0; i < simplest_db.size(); i++){
        cout << simplest_db[i].first << ", " << simplest_db[i].second << endl;
    }



    // Setup:
    EncryptionParameters enc_params(scheme_type::cgsw1);
    enc_params.set_security_level(2);
    enc_params.set_rate(0.2);
    enc_params.compute();

    cout << "Enc params" << enc_params << endl;

    KeyGenerator keygen(enc_params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encrypter encryptor(enc_params, public_key);
    Evaluator evaluator(enc_params);
    Decrypter decryptor(enc_params, secret_key);

    /*
     * Server setup:
     * input: database
     * output: encrypted database
     */
    std::vector<CGSWCiphertext> encrypted_db;
    int n = simplest_db.size();

    // plaintext encoding + ciphertext encryption
    int no_slots = enc_params.getNumSlots();
    int slot_max = enc_params.getP();
    int n0 = enc_params.getLatticeDimension0();
    cout << "number of plaintext slots: " << no_slots << endl;
    for (int i = 0; i < n ; i ++){
        // plaintext encoding
        // for simplest_int, it's simply the first element
        CGSW_mat_uint m;
        m.SetDims(n0, n0);
        m[0][0] = simplest_db[i].second;
        CGSWPlaintext p(enc_params, m);
        p.generate_bit_decomposed_plaintexts();

        // ciphertext encryption
        CGSWCiphertext c;
        encryptor.encrypt_compress(p, c);

        // push back
        encrypted_db.push_back(c);
    }

    /*
     * Client:
     * input: target, n
     * output: query
     */
    int target = 1; // element 2
    std::vector<GSWCiphertext> query;

    for (int i = 0; i < n; i ++){
        if(i != target) {
            GSWPlaintext p0(0);
            GSWCiphertext c0;
            encryptor.encrypt_gsw(p0, c0);
            query.push_back(c0);
        } else {
            GSWPlaintext p1(1);
            GSWCiphertext c1;
            encryptor.encrypt_gsw(p1, c1);
            query.push_back(c1);
        }
    }


    /*
     * Server calc reply:
     * input: query, encrypted_db
     * output: reply
     */
    CGSWCiphertext reply;

    // first round
    evaluator.multiply_inplace_gsw(encrypted_db[0], query[0]);
    reply = encrypted_db[0];

    // remaning round of multiply then sum
    for(int i = 1; i < n; i ++){
        evaluator.multiply_inplace_gsw(encrypted_db[i], query[i]);
        evaluator.add_inplace(reply, encrypted_db[i]);
    }




    /*
     * Client decrypt reply:
     * input: reply
     * output: final result
     */

    CGSWPlaintext p_ans;
    decryptor.compressed_decrypt(reply, p_ans);

    cout << "p_ans: " << p_ans.data() << endl;
    cout << "final_ans: " << p_ans.data()[0][0] << endl;


    return 0;
}

