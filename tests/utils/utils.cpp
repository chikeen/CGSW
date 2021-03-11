//
// Created by Chi Keen Tan on 13/01/2021.
//
#include "../catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;


TEST_CASE("Utils Number Theory Tests"){
    auto bits = GENERATE(8, 16, 32, 64, 128, 256);

    SECTION("Test getPrime bitSize"){
        CGSW_long p = util::gen_prime(bits);
        REQUIRE(NTL::NumBits(p) == bits);
    }

    SECTION("Test round_division"){
        REQUIRE(util::round_division(7, 3) == 2);
        REQUIRE(util::round_division(58, 4) == 15);
        REQUIRE(util::round_division(58, 5) == 12);
    }
}

TEST_CASE("Utils Matrix Tests"){

    auto k = GENERATE(4, 16);
    EncryptionParameters params(scheme_type::gsw);
    params.set_circuit_depth(3);
    params.set_security_level(k);
    params.compute();

    auto q = params.getCipherModulus();
    auto n = params.getLatticeDimension0();
    auto m = params.getM();
    auto l_q = params.getQL();
    CGSW_mod::init(q);

    INFO("params: \n" << params);

    SECTION("test gen_random_matrix"){
        CGSW_mat a, b;
        util::gen_random_matrix(a, n, m);
        util::gen_random_matrix(b, n, m);
        INFO("a:" << a);
        INFO("b:" << b);

        SECTION("random ? "){
            REQUIRE_FALSE(a == b);
        }
    }

    SECTION("test gen_random_matrix_limit"){
        CGSW_mat a, b;
        util::gen_random_matrix(a, n, m,3);
        util::gen_random_matrix(b, n, m,3);
        INFO("a:" << a);
        INFO("b:" << b);

        SECTION("random ? "){
            REQUIRE_FALSE(a == b);
        }

        SECTION("limit ? "){
            REQUIRE(rep(a[0][0]) < 3);
            REQUIRE(util::get_sum(a) < 3 * n * m);
        }
    }

    SECTION("test gen_empty_matrix"){
        CGSW_mat a;
        util::gen_empty_matrix(a, n, m);
        INFO("a:" << a);

        SECTION("empty? "){
            REQUIRE(NTL::IsZero(a));
            REQUIRE(a[0][0] == 0);
        }

        a[0][0] = 1;
        SECTION("not empty? "){
            REQUIRE_FALSE(NTL::IsZero(a));
            REQUIRE_FALSE(a[0][0] == 0);
        }
    }

    SECTION("test gen_normal_matrix"){
        CGSW_mat a, b;
        util::gen_normal_matrix(a, n, m);
        util::gen_normal_matrix(b, n, m);
        INFO( "a:" << a);
        INFO( "b:" << b);

        SECTION("random? "){
            REQUIRE_FALSE(a == b);
            REQUIRE( 1== 2);
        }
        // TODO:- How to test normal ?
    }

    SECTION("test gen_gadget_matrix"){
        CGSW_mat a;
        util::gen_gadget_matrix(a, n, m);
        INFO( "a:" << a);

        SECTION("size ? "){
            REQUIRE(a.NumRows() == n);
            REQUIRE(a.NumCols() == m);
        }
    }

    SECTION("test bit_decompose_matrix"){

        SECTION("test G then G-1") {
            CGSW_mat random, g;

            // Generate a random matrix
            util::gen_random_matrix(random, n, m);
            INFO( "random:" << random);

            // G
            util::gen_gadget_matrix(g, n, m);
            INFO( "g:" << g);

            // C = G . G-1(C)
            CGSW_mat g_inverse_random;
            util::bit_decompose_matrix(g_inverse_random, random, l_q);
            INFO( "g_inverse_random:" << g_inverse_random);

            CGSW_mat random_p = g * g_inverse_random;

            REQUIRE(random.NumRows() == random_p.NumRows());
            REQUIRE(random.NumCols() == random_p.NumCols());
            REQUIRE(random == random_p);
        }
    }
}
