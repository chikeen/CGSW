
#pragma once

#include <vector>
#include <cgsw/cgsw.hpp>


typedef std::vector<cgsw::GSWCiphertext> PIRQuery;
typedef cgsw::CGSWCiphertext PIRReply;
typedef std::vector<std::pair<std::string, std::string>> stringDatabase;
typedef std::vector<cgsw::CGSWCiphertext> encryptedDatabase;

class PIRClient {

    public:
        PIRClient(cgsw::EncryptionParameters enc_params) :enc_params_(enc_params){
            cgsw::KeyGenerator keygen(enc_params_);
            sk_ = keygen.secret_key();
            pk_ = keygen.create_public_key();
        }

        cgsw::PublicKey getPublicKey () const{
            return pk_;
        }

        PIRQuery generate_query(size_t index, size_t database_size);

        PIRQuery generate_compressed_query(size_t index, size_t database_size);

        std::string extract_reply(const cgsw::CGSWCiphertext& reply);

    private:

        cgsw::EncryptionParameters enc_params_;

        cgsw::SecretKey sk_;

        cgsw::PublicKey pk_;
};

inline char string_decoding(int input, int range){
    // ASCII encoding range from 0 -> 127
    int multiply = range/128;

    return char(input/multiply);
}