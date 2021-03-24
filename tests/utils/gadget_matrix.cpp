//
// Created by Chi Keen Tan on 16/03/2021.
//

#include "../catch.hpp"
#include <cgsw/cgsw.hpp>

using namespace cgsw;
using namespace std;

TEST_CASE("CGSW1 Gadget Matrix Test"){

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

    SECTION("test gen_g_gadget_matrix"){
        CGSW_mat a;
        util::gen_g_gadget_matrix(a, n, m);
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
            util::gen_g_gadget_matrix(g, n, m);
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


TEST_CASE("CGSW2 Gadget Matrix Tets"){

    auto k = GENERATE(2);
//    EncryptionParameters params(scheme_type::cgsw2);
//    params.set_circuit_depth(3);
//    params.set_security_level(k);
//    params.compute();

//    auto q = params.getCipherModulus();
//    auto n0 = params.getLatticeDimension0();
//    auto n1 = params.getLatticeDimension1();
//    auto n2 = params.getLatticeDimension2();
//    auto m = params.getM();
//    auto l_q = params.getQL();

//    CGSW_long q {7};
    auto n0 = 6;
    auto n1 = 7;
    auto n2 = 9;
    auto m = 18;
    auto l_q = 3;
    auto r = 3, t = 3;


    CGSW_mod::init(CGSW_long {3});
//
//    INFO("params: \n" << params);

    SECTION("F'"){
        CGSW_mat f;
        util::gen_f_prime(f, 2, 2);
        INFO( "f" << f);
//        REQUIRE( 1 == 2);
    }

    SECTION("F"){
        CGSW_mat f;
        util::gen_f_trapdoor_matrix(f, 2, 3);
        INFO( "f" << f);
//        REQUIRE( 1 == 2);
    }


    SECTION("H"){

        CGSW_long q {3};
        CGSW_mat H;
        util::gen_h_gadget_matrix(H, 2);
        INFO( "H" << H);
//        REQUIRE( 1 == 2);

        CGSW_mat f;
        util::gen_f_trapdoor_matrix(f, 2, 2);
        CGSW_mat HF = H * f;
        INFO("HF" << rep(HF));
        REQUIRE( 1 == 2);
    }

}