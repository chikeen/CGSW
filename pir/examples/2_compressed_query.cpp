//
// Created by Chi Keen Tan on 19/05/2021.
//

#include <chrono>
#include "../client/client.hpp"
#include "../server/server.hpp"
#include "examples.hpp"

using namespace std;
using namespace cgsw;
using namespace std::chrono;


void example_compressed_query(){

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

    for(auto & i : simplest_db){
        cout << i.first << ", " << i.second << endl;
    }

    cout << "Encrypting database......." << endl;
    auto start = high_resolution_clock::now();
    server.encryptDatabase(client.getPublicKey(), simplest_db);
    auto stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    cout << "Client generating query ......." << endl;
    int target = 1; // 2nd element
    start = high_resolution_clock::now();
    PIRQuery query = client.generate_compressed_query(target, server.getDatabaseSize());
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count()
            << ", (seconds)" << duration_cast<seconds>(stop - start).count() << endl;

    cout << "Server generating reply ......." << endl;
    start = high_resolution_clock::now();
    PIRReply reply = server.generateReplyCompressedQuery(query);
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;

    cout << "Client decrypting reply ......." << endl;
    start = high_resolution_clock::now();
    std::string answer = client.extract_reply(reply);
    stop = high_resolution_clock::now();
    cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << endl;
    cout << "final answer: " << answer << ";" << endl;

}