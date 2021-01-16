//
// Created by Chi Keen Tan on 13/01/2021.
//

#include "../catch.hpp"
#include "../../src/cgsw/utils/utils.h"

using namespace cgsw::util;
using namespace std;

TEST_CASE("Utils Tests"){
    using record = std::tuple<uint64_t , uint64_t>;
    auto extent = GENERATE(table<uint64_t , uint64_t>({
                          record{8, 89},
                          record{16, 25523},
                          record{24, 7332551}}));
    uint64_t d = 3,
            k = std::get<0>(extent),
            n = k,
            q = std::get<1>(extent),
            l = ceil(log2(q)),
            m = l * n;

    SECTION("test gen_random_matrix"){
        dynMatrix a = gen_random_matrix(n, n, q);
        dynMatrix b = gen_random_matrix(n, n, q);

        SECTION("random ? "){
            REQUIRE_FALSE(a == b);
        }

        SECTION("highest? "){
            REQUIRE(a.maxCoeff() < q);
            REQUIRE(b.maxCoeff() < q);
        }
    }

    SECTION("test gen_empty_matrix"){
        SECTION("empty? "){
            dynMatrix a = gen_empty_matrix(n, n);
            REQUIRE(a.sum() == 0);
        }
    }

    SECTION("test gen_normal_matrix"){
        dynMatrix a = gen_normal_matrix(n,n, q);
        dynMatrix b = gen_normal_matrix(n,n, q);

        SECTION("random? "){
            REQUIRE_FALSE(a == b);
        }

        SECTION("highest? "){
            REQUIRE(a.maxCoeff() < q);
            REQUIRE(b.maxCoeff() < q);
        }
    }

    SECTION("test gen_gadget_matrix"){
        SECTION("size ? "){
            dynMatrix a = gen_gadget_matrix(n, m);
            REQUIRE(a.rows() == n);
            REQUIRE(a.cols() == m);
        }
    }

    SECTION("test bit_decompose_matrix"){
        SECTION("test G then G-1") {
            // Generate a random matrix
            dynMatrix random = gen_random_matrix(n, m, q);

            // G
            dynMatrix g = gen_gadget_matrix(n, m);

            // C = G . G-1(C)
            dynMatrix g_inverse_random = bit_decompose_matrix(random, l);

            dynMatrix random_p = g * g_inverse_random;
            modulo_matrix(random_p, q);

            REQUIRE(random.cols() == random_p.cols());
            REQUIRE(random.rows() == random_p.rows());
            REQUIRE(random == random_p);
        }
    }
}
