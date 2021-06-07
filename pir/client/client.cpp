//
// Created by Chi Keen Tan on 10/05/2021.
//

#include "client.hpp"

using namespace std;
using namespace cgsw;

PIRQuery PIRClient::generate_query(size_t index, size_t database_size) {
    cgsw::Encrypter encryptor(enc_params_, pk_);
    PIRQuery query;

    for (int i = 0; i < database_size; i ++){
        if(i != index) {
            GSWPlaintext p0(0);
            GSWCiphertext c0;
            encryptor.encrypt_gsw(p0, c0);
            query.push_back(c0);
        } else {
            GSWPlaintext p1(1);
            GSWCiphertext c1;
            encryptor.encrypt_gsw(p1, c1);
            query.push_back(c1);
        }
    }

    return query;
}


PIRQuery PIRClient::generate_compressed_query(size_t index, size_t database_size) {
    cgsw::Encrypter encryptor(enc_params_, pk_);
    PIRQuery query;

    // dimension of query is 2 x query_2nd_dimension)
    int query_2nd_dimension = ceil(log2(database_size));

    for(int i = 0; i < query_2nd_dimension; i ++){
        auto m = bit(index, i );
        GSWPlaintext p (bit(index, i));
        GSWCiphertext c;
        encryptor.encrypt_gsw(p, c);
        query.push_back(c);
    }

    return query;
}

std::string PIRClient::extract_reply(const cgsw::CGSWCiphertext& reply){
    cgsw::Decrypter decryptor(enc_params_, sk_);
    int decryption_range = enc_params_.getF();

    CGSWPlaintext p_ans(enc_params_);
    decryptor.compressed_decrypt(reply, p_ans);

    cout << "p_ans: " << p_ans.data() << endl;
    std::string answer;
    for(int i = 0; i < enc_params_.getNumSlots(); i ++){
        answer += string_decoding(p_ans.at(i), decryption_range);
    }

    return answer;
}
