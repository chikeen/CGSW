#include "server.hpp"

using namespace std;
using namespace cgsw;


PIRReply PIRServer::generate_reply(PIRQuery query) {
    Evaluator evaluator(enc_params_);


    /// first round
    evaluator.multiply_inplace_gsw(enc_db_[0], query[0]);
    PIRReply reply = enc_db_[0];

    /// remaning round of multiply then sum
    for(int i = 1; i < enc_db_.size(); i ++){
        evaluator.multiply_inplace_gsw(enc_db_[i], query[i]);
        evaluator.add_inplace(reply, enc_db_[i]);
    }

    return reply;
}

PIRReply PIRServer::generate_reply_compressed_query(PIRQuery query) {
    Evaluator evaluator(enc_params_);
    Encrypter encrypter(enc_params_, pk_);

    /// extract compressed query
    GSWPlaintext p1 (1);
    GSWCiphertext c1;
    encrypter.encrypt_gsw(p1, c1);

    std::vector<std::vector<GSWCiphertext>> compressed_query;

    for (const auto & i : query){
        std::vector<GSWCiphertext> tmp;
        GSWCiphertext c_ans;
        evaluator.sub(c1, i, c_ans);
        tmp.push_back(c_ans);
        cout << "c_ans:" << c_ans.data() << endl;
        tmp.push_back(i);
        cout << "i:" << i.data() << endl;


        compressed_query.push_back(tmp);
    }

    /// first round
    PIRReply acc = enc_db_[0];
    multiply_compressed_query(compressed_query, evaluator, acc, 0);
    PIRReply reply = acc;

    /// remaning round of multiply then sum
    for(int i = 1; i < enc_db_.size(); i ++){
        auto acc2 = enc_db_[i];
        multiply_compressed_query(compressed_query, evaluator, acc2, i);
        evaluator.add_inplace(reply, acc2);
    }

    return reply;
}

void PIRServer::encrypt_database(cgsw::PublicKey pk, stringDatabase db) {
    db_ = std::move(db);
    pk_ = std::move(pk);

    int n = db_.size();
    Encrypter encryptor(enc_params_, pk_);

    // plaintext encoding + ciphertext encryption
    int no_slots = enc_params_.getNumSlots();
    int decryption_range = enc_params_.getF();
    cout << "number of plaintext slots: " << no_slots << endl;
    for (int i = 0; i < n ; i ++){
        /// plaintext encoding
        // for simplest_str, ascii encoding is used

        cgsw::CGSWPlaintext p(enc_params_);
        for(int j = 0; j < db_[i].second.size(); j ++){
            p.at(j) = string_encoding(db_[i].second[j], decryption_range);
        }

        for(int j = db_[i].second.size(); j < no_slots; j ++){
            p.at(j) = 0;
        }

        cout << p.data() << endl;
        p.generate_bit_decomposed_plaintexts();

        /// ciphertext encryption
        CGSWCiphertext c;
        encryptor.encrypt_compress(p, c);

        /// push back
        enc_db_.push_back(c);
    }
}

void PIRServer::multiply_compressed_query(const std::vector<std::vector<cgsw::GSWCiphertext>> &query, cgsw::Evaluator & evaluator, PIRReply &acc, size_t location) {
    /// first round
    if(bit(location, 0)){
        evaluator.multiply_inplace_gsw(acc, query[0][1]);
    }
    else{
        evaluator.multiply_inplace_gsw(acc, query[0][0]);
    }

    /// remaining rounds
    for(int i = 1; i < query.size(); i ++){
        if(bit(location, i)){
            evaluator.multiply_inplace_gsw(acc, query[i][1]);
        }
        else{
            evaluator.multiply_inplace_gsw(acc, query[i][0]);
        }
    }
}