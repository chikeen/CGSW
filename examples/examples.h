//
// Created by Chi Keen Tan on 18/12/2020.
//

#pragma once

#include <iostream>
#include <iomanip>
#include <cgsw/cgsw.h>


void example_gsw_basics();



/*
Helper function: Prints the name of the example in a fancy banner.
*/
inline void print_example_banner(std::string title)
{
    if (!title.empty())
    {
        std::size_t title_length = title.length();
        std::size_t banner_length = title_length + 2 * 10;
        std::string banner_top = "+" + std::string(banner_length - 2, '-') + "+";
        std::string banner_middle = "|" + std::string(9, ' ') + title + std::string(9, ' ') + "|";

        std::cout << std::endl << banner_top << std::endl << banner_middle << std::endl << banner_top << std::endl;
    }
}

/*
Helper function: Print line number.
*/
inline void print_line(int line_number)
{
    std::cout << "Line " << std::setw(3) << line_number << " --> ";
}


/*
Helper function: Prints the parameters in a SEALContext.
*/
inline void print_parameters(const cgsw::EncryptionParameters &params) {


    /*
    Which scheme are we using?
    */
    std::string scheme_name;
    switch (params.scheme())
    {
        case cgsw::scheme_type::gsw:
            scheme_name = "GSW";
            break;
        case cgsw::scheme_type::cgsw1:
            scheme_name = "RGSW";
            break;
        default:
            throw std::invalid_argument("unsupported scheme");
    }
    std::cout << "/" << std::endl;
    std::cout << "| Encryption parameters :" << std::endl;
    std::cout << "|   scheme: " << scheme_name << std::endl;
    std::cout << "|   sec_level (k): " << params.getSecLevel() << std::endl;
    std::cout << "|   depth (d): " << params.getDepth() << std::endl;
    std::cout << "|   modulus (p): " << params.getCipherModulus() << std::endl;
    std::cout << "|   lattice_dimension (n): " << params.getLatticeDimension0() << std::endl;
    std::cout << "|   M (lattice_dimension * log(modulus)): " << params.getM() << std::endl;

    std::cout << "\\" << std::endl;
}

