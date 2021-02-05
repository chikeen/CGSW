//
// Created by Chi Keen Tan on 13/01/2021.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/cgsw/keygenerator.h"

using namespace cgsw;
using namespace std;

/*
 * Cases (k, q):
 *  1. 8, 89
 *  2. 16, 25523
 *  3. 24, 7332551
 */

TEST_CASE("Key Generator"){

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
