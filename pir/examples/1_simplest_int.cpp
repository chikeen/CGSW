//
// Created by Chi Keen Tan on 19/05/2021.
//


#include "../client/client.hpp"
#include "../server/server.hpp"
#include "examples.hpp"

using namespace std;
using namespace cgsw;

void example_simplest_str(){

    auto rate = 0.2;
    auto k = 2;

    std::string db_filename = "./data/simplest_str.csv";

    /************ Setup ****************************/
    EncryptionParameters enc_params(scheme_type::cgsw1);
    enc_params.set_security_level(k);
    enc_params.set_rate(rate);
    enc_params.compute();

    PIRClient client(enc_params);
    PIRServer server(enc_params);

    cout << "Enc params" << enc_params << endl;

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

    cout << "Encrypting database......." << endl;
    server.encryptDatabase(client.getPublicKey(), simplest_db);

    cout << "Client generating query ......." << endl;
    int target = 1; // 2nd element
    PIRQuery query = client.generate_query(target, server.getDatabaseSize());


    cout << "Server generating reply ......." << endl;
    PIRReply reply = server.generateReply(query);


    cout << "Client decrypting reply ......." << endl;

    std::string answer = client.extract_reply(reply);
    cout << "final answer: " << answer << ";" << endl;

}