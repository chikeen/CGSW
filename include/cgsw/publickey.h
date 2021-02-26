//
// Created by Chi Keen Tan on 19/12/2020.
//

#pragma once

#include "common.h"


namespace cgsw {

    class PublicKey {
        
        friend class KeyGenerator;

        public:
            /**
           Creates an empty public key.
           */
            PublicKey() = default;

            /**
            Creates a new PublicKey by copying an old one.

            @param[in] copy The PublicKey to copy from
            */
            PublicKey(const PublicKey &copy) = default;

            /**
            Creates a new PublicKey by moving an old one.

            @param[in] source The PublicKey to move from
            */
            PublicKey(PublicKey &&source) = default;

            /**
            Copies an old PublicKey to the current one.

            @param[in] assign The PublicKey to copy from
            */
            PublicKey &operator=(const PublicKey &assign) = default;

            /**
            Moves an old PublicKey to the current one.

            @param[in] assign The PublicKey to move from
            */
            PublicKey &operator=(PublicKey &&assign) = default;

            /**
            Returns a reference to the underlying data.
            */
            inline auto &data() noexcept
            {
                return pk_;
            }

            /**
            Returns a const reference to the underlying data.
            */
            inline auto &data() const noexcept
            {
                return pk_;
            }

        private:
            CGSW_mat pk_;

    };
}