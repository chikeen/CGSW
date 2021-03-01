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
}

TEST_CASE("Utils Matrix Tests"){

    auto k = GENERATE(4, 16, 128);
    EncryptionParameters params(scheme_type::gsw);
    params.set_circuit_depth(3);
    params.set_security_level(k);

    auto q = params.getCipherModulus();
    auto n = params.getLatticeDimension0();
    auto m = params.getLatticeDimension1();
    auto l = params.getL();
    CGSW_mod::init(q);

    SECTION("test gen_random_matrix"){
        CGSW_mat a, b;
        util::gen_random_matrix(a, n, m);
        util::gen_random_matrix(b, n, m);

        SECTION("random ? "){
            REQUIRE_FALSE(a == b);
        }
    }

    SECTION("test gen_empty_matrix"){
        SECTION("empty? "){
            CGSW_mat a;
            util::gen_empty_matrix(a, n, m);
            REQUIRE(NTL::IsZero(a));
            REQUIRE(a(5, 4) == 0);
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
            REQUIRE(1 ==2);
        }

        // How to test normal ?
    }

    SECTION("test gen_gadget_matrix"){
        auto n = 16, m = 96;

        SECTION("size ? "){
            CGSW_mat a;
            util::gen_gadget_matrix(a, n, m);
            INFO( "a:" << a);
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
            util::bit_decompose_matrix(g_inverse_random, random, l);
            INFO( "g_inverse_random:" << g_inverse_random);

            CGSW_mat random_p = g * g_inverse_random;

            REQUIRE(random.NumRows() == random_p.NumRows());
            REQUIRE(random.NumCols() == random_p.NumCols());
            REQUIRE(random == random_p);
        }
    }
}
