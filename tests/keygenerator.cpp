//
// Created by Chi Keen Tan on 13/01/2021.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <cgsw/cgsw.h>

using namespace cgsw;
using namespace std;

/*
 * Cases (k, q):
 *  1. 8, 89
 *  2. 16, 25523
 *  3. 24, 7332551
 */

TEST_CASE("GSW: Key Generator"){

    using record = std::tuple<uint64_t , uint64_t>;
    auto extent = GENERATE(table<uint64_t , uint64_t>({
                              record{8, 89},
                              record{16, 25523},
                              record{24, 7332551}
    }));
    uint64_t d = 3,
            k = std::get<0>(extent),
            n = k;
    matrixElemType q(std::get<1>(extent));
    uint64_t l = ceil(log2(q)),
            m = l * n;

    EncryptionParameters parms(scheme_type::gsw);
    parms.set_circuit_depth(d);
    parms.set_security_level(k);
    parms.set_cipher_modulus(q);

    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    SECTION("Secret_key size"){
        REQUIRE(secret_key.sk().rows() == 1);
//        REQUIRE(secret_key.sv().rows() == 1);
        REQUIRE(secret_key.sk().cols() == n);
//        REQUIRE(secret_key.sv().cols() == n-1);
    }

    SECTION("Public_key size"){
        INFO("Modulus, q" << q);
        INFO("Modulus2, q " << parms.getCipherModulus());

        REQUIRE(public_key.data().rows() == n);
        REQUIRE(public_key.data().cols() == m);
    }

    SECTION("Public_key * Secret_key must equal small errors"){

        INFO("q: " << q );
        dynMatrix product =  secret_key.sk() * public_key.data();
        INFO("product(before): " << product );
        util::modulo_matrix(product, matrixElemType (q));
        INFO("product: " << product );
        cout << "error: " << product << endl;
        REQUIRE(product.norm() < n * q/2); // average size less than q/2
    }
}

TEST_CASE("CGSW: Key Generator"){
    auto k = GENERATE(16);
    auto p_bits = 16;

    EncryptionParameters parms(scheme_type::cgsw);
    parms.set_circuit_depth(3);
    parms.set_security_level(k);
    parms.set_plaintext_space_in_bit(p_bits);
    parms.set_rate(0.8);

    KeyGenerator keygen(parms);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);

    auto m = parms.getM();
    auto q = parms.getCipherModulus();
    auto n1 = parms.getLatticeDimension1();
    auto n0 = parms.getLatticeDimension0();
    INFO("Parms" << parms);

    SECTION("Secret_key size"){
        REQUIRE(secret_key.sk().rows() == n0);
//        REQUIRE(secret_key.sv().rows() == n0);
        REQUIRE(secret_key.sk().cols() == n1);
//        REQUIRE(secret_key.sv().cols() == n1);
    }

    SECTION("Public_key size"){
        REQUIRE(public_key.data().rows() == n1);
        REQUIRE(public_key.data().cols() == m);
    }

    SECTION("Public_key * Secret_key must equal small errors"){
        dynMatrix product =  secret_key.sk() * public_key.data();
        INFO("product(before): " << product );
        util::modulo_matrix(product, matrixElemType (q));
        INFO("product: " << product );
        REQUIRE(product.norm() < n0 * q/2); // average size less than q/2
    }
}
