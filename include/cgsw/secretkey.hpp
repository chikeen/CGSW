//
// Created by Chi Keen Tan on 19/12/2020.
//

#pragma once

#include "common.hpp"
#include "plaintext.hpp"

namespace cgsw {

    /**
     * SecretKey is going to be a matrix of size 1 x n
     *
     */
    class SecretKey {

        friend class KeyGenerator;

    public:
        /**
        Creates an empty secret key.
        */
        SecretKey() = default;

        /**
        Creates a new SecretKey by copying an old one.

        @param[in] copy The SecretKey to copy from
        */
        SecretKey(const SecretKey &copy)
        {
            // Note: sk_ is at this point initialized to use a custom (new)
            // memory pool with the `clear_on_destruction' property. Now use
            // Plaintext::operator =(const Plaintext &) to copy over the data.
            // This is very important to do right, otherwise newly created
            // SecretKey may use a normal memory pool obtained from
            // MemoryManager::GetPool() with currently active profile (MMProf).
            sk_ = copy.sk_;
        }

        /**
        Destroys the SecretKey object.
        */
        ~SecretKey() = default;

        /**
       Creates a new SecretKey by moving an old one.

       @param[in] source The SecretKey to move from
       */
        SecretKey(SecretKey &&source) = default;

        /**
        Copies an old SecretKey to the current one.

        @param[in] assign The SecretKey to copy from
        */
//        SecretKey &operator=(const SecretKey &assign)
//        {
//            Plaintext new_sk(MemoryManager::GetPool(mm_prof_opt::mm_force_new, true));
//            new_sk = assign.sk_;
//            std::swap(sk_, new_sk);
//            return *this;
//        }

        /**
        Moves an old SecretKey to the current one.

        @param[in] assign The SecretKey to move from
        */
        SecretKey &operator=(SecretKey &&assign) = default;

        inline auto &sk() noexcept
        {
            return sk_;
        }

        inline auto &sk() const noexcept
        {
            return sk_;
        }

        inline auto &sv() noexcept
        {
            return sv_;
        }

        inline auto &sv() const noexcept
        {
            return sv_;
        }

    private:

        CGSW_mat sk_ {};

        CGSW_mat sv_ {};
    };
}