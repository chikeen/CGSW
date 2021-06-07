
#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cgsw/cgsw.hpp>

#include "../client/client.hpp"



class PIRServer {

public:
    PIRServer(cgsw::EncryptionParameters enc_params) :enc_params_(enc_params){}

    void encrypt_database(cgsw::PublicKey pk, stringDatabase db);

    PIRReply generate_reply(PIRQuery query);

    PIRReply generate_reply_compressed_query(PIRQuery query);

    size_t getDatabaseSize(){
        return db_.size();
    }



private:

    static void multiply_compressed_query(const std::vector<std::vector<cgsw::GSWCiphertext>> & query, cgsw::Evaluator & evaluator, PIRReply & acc, size_t location);

    cgsw::EncryptionParameters enc_params_;

    stringDatabase db_;

    encryptedDatabase enc_db_;

    cgsw::PublicKey pk_;
};



inline std::vector<std::pair<int, int>> read_csv_int_int(std::string filename){
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

inline std::vector<std::pair<std::string, std::string>> read_csv_str_str(std::string filename){
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

inline int string_encoding(char input, int range){
    // ASCII encoding range from 0 -> 127
    int multiply = range/128;

    return int(input) * multiply;
}