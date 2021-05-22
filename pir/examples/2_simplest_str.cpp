//
// Created by Chi Keen Tan on 19/05/2021.
//


#include "examples.hpp"

using namespace std;
using namespace cgsw;


void example_simplest_str(){

    auto rate = 0.2;
    auto k = 2;

    std::string db_filename = "./data/simplest_str.csv";
    bool debug = false;

    std::cout << "---Initialising HE Environment ...\n ";
    // Initialize context
    // This object will hold information about the algebra used for this scheme.
    std::cout << "Initializing the Context ...\n";

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_rate(rate);
    params.set_security_level(k);
    params.compute();


    /************ Read in the database ************/
    std::vector<std::pair<std::string, std::string>> simplest_db;
    try {
        simplest_db = read_csv_str_str(db_filename);
    } catch (std::runtime_error& e) {
        std::cerr << "\n" << e.what() << std::endl;
        exit(1);
    }

    for(int i = 0; i < simplest_db.size(); i++){
        cout << simplest_db[i].first << ", " << simplest_db[i].second << endl;
    }


    /************ Setup ****************************/
    EncryptionParameters enc_params(scheme_type::cgsw1);
    enc_params.set_security_level(k);
    enc_params.set_rate(rate);
    enc_params.compute();

    cout << "Enc params" << enc_params << endl;

    KeyGenerator keygen(enc_params);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key = keygen.create_public_key();

    Encrypter encryptor(enc_params, public_key);
    Evaluator evaluator(enc_params);
    Decrypter decryptor(enc_params, secret_key);


    /************ Server Setup ****************************/
    /*
     * input: database
     * output: encrypted database
     */

    std::vector<CGSWCiphertext> encrypted_db;
    int n = simplest_db.size();

    // plaintext encoding + ciphertext encryption
    int no_slots = enc_params.getNumSlots();
    int slot_max = enc_params.getP();
    int decryption_range = enc_params.getF();
    int n0 = enc_params.getLatticeDimension0();
    cout << "number of plaintext slots: " << no_slots << endl;
    for (int i = 0; i < n ; i ++){
        /// plaintext encoding
        // for simplest_str, ascii encoding is used

        CGSWPlaintext p(enc_params);
        for(int j = 0; j < simplest_db[i].second.size(); j++){
            p.at(j) = string_encoding(simplest_db[i].second[j], decryption_range);
        }
        cout << p.data() << endl;
        p.generate_bit_decomposed_plaintexts();

        /// ciphertext encryption
        CGSWCiphertext c;
        encryptor.encrypt_compress(p, c);

        /// push back
        encrypted_db.push_back(c);
    }


    /************ Client Query ****************************/
    /*
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

    /************ Server calc reply ****************************/
    /*
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


    /************ Client decrypt reply ****************************/
    /*
     * input: reply
     * output: final result
     */

    CGSWPlaintext p_ans;
    decryptor.compressed_decrypt(reply, p_ans);

    cout << "p_ans: " << p_ans.data() << endl;
    std::string answer = "";
    for(int i = 0; i < no_slots; i ++){
        answer += string_decoding( p_ans.at(i), decryption_range);
    }

    cout << "final answer: " << answer << ";" << endl;

}