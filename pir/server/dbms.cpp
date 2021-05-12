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

// Utility function to read <K,V> CSV data from file
std::vector<std::pair<std::string, std::string>> read_csv(std::string filename){
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

    std::string db_filename = "./data/country_dataset_minimal.csv";
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

    std::cout << "---Initialising HE Environment ... ";
    // Initialize context
    // This object will hold information about the algebra used for this scheme.
    std::cout << "\nInitializing the Context ... ";

    EncryptionParameters params(scheme_type::cgsw1);
    params.set_rate(rate);
    params.set_security_level(k);
    params.compute();

    if (debug) std::cout << params << std::endl;

    /************ Read in the database ************/
    std::vector<std::pair<std::string, std::string>> country_db;
    try {
        country_db = read_csv(db_filename);
    } catch (std::runtime_error& e) {
        std::cerr << "\n" << e.what() << std::endl;
        exit(1);
    }



    return 0;
}

