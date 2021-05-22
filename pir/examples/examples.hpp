//
// Created by Chi Keen Tan on 19/05/2021.
//

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <cgsw/cgsw.hpp>



void example_simplest_int();
void example_simplest_str();

// Utility functions to read <K,V> CSV data from file

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

inline char string_decoding(int input, int range){
    // ASCII encoding range from 0 -> 127
    int multiply = range/128;

    return char(input/multiply);
}



