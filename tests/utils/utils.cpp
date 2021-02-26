//
// Created by Chi Keen Tan on 13/01/2021.
//
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw::util;
using namespace std;


TEST_CASE("Utils Number Theory Tests"){
    auto bits = GENERATE(8, 16, 32, 64, 128, 256);

    SECTION("Test getPrime bitSize"){
        CGSW_long p = gen_prime(bits);
        REQUIRE(NTL::NumBits(p) == bits);
    }
}

TEST_CASE("Utils Matrix Tests"){

    auto p_bits = GENERATE(8, 16, 128);
    auto p = gen_prime(p_bits);
    CGSW_mod::init(p);

    SECTION("test gen_random_matrix"){
        CGSW_mat a, b;
        gen_random_matrix(a, 10, 10);
        gen_random_matrix(b, 10, 10);

        SECTION("random ? "){
            REQUIRE_FALSE(a == b);
        }
    }

    SECTION("test gen_empty_matrix"){
        SECTION("empty? "){
            CGSW_mat a;
            gen_empty_matrix(a, 10, 10);
            REQUIRE(NTL::IsZero(a));
            REQUIRE(a(5, 4) == 0);
        }
    }

    SECTION("test gen_normal_matrix"){
        CGSW_mat a, b;

        gen_normal_matrix(a, 10, 10);
        gen_normal_matrix(b, 10, 10);

        INFO( "a:" << a);
        INFO( "b:" << b);
        SECTION("random? "){
            REQUIRE_FALSE(a == b);
            REQUIRE(1 ==2);
        }

        // How to test normal ?
    }

    SECTION("test gen_gadget_matrix"){
        auto n = 16, m = 96;

        SECTION("size ? "){
            CGSW_mat a;
            gen_gadget_matrix(a, n, m);
            REQUIRE(a.NumRows() == n);
            REQUIRE(a.NumCols() == m);
        }
    }

//    SECTION("test bit_decompose_matrix"){
//        SECTION("test G then G-1") {
//            // Generate a random matrix
//            CGSW_mat random = gen_random_matrix(n, m, q);
//
//            // G
//            CGSW_mat g = gen_gadget_matrix(n, m);
//
//            // C = G . G-1(C)
//            CGSW_mat g_inverse_random = bit_decompose_matrix(random, l);
//
//            CGSW_mat random_p = g * g_inverse_random;
//            modulo_matrix(random_p, q);
//
//            REQUIRE(random.cols() == random_p.cols());
//            REQUIRE(random.rows() == random_p.rows());
//            REQUIRE(random == random_p);
//        }
//    }
}
