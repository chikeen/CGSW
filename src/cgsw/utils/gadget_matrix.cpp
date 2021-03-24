//
// Created by Chi Keen Tan on 11/03/2021.
//

#include "../../../include/cgsw/utils/gadget_matrix.hpp"
#include "../../../include/cgsw/utils/matrix.hpp"


namespace cgsw {
    namespace util {

        void gen_g_gadget_matrix(CGSW_mat& mat, size_t n, size_t m){
            if(m < n) throw std::runtime_error("gadget matrix cols must > rows");

            mat.SetDims(n, m);
            int no_log = m/n; // TODO:- is this really the best way?

            for(int i = 0 ; i < n; i++){
                for(int l = 0; l < no_log; l++){
                    mat[i][no_log*i + l] = pow(2, l);
                }
            }
        }

        void bit_decompose_matrix(CGSW_mat& mat_out, const CGSW_mat& mat_in, uint64_t l){
            /*
             * Take a nxc matrix and make it mxc
             */
            uint64_t n = mat_in.NumRows();
            uint64_t c = mat_in.NumCols();
            uint64_t m = n * l;

            mat_out.SetDims(m, c);

            for(int j = 0; j < c; j ++){
                for(int i = 0; i < n; i++){
                    for(int k = 0; k < l; k++){
                        mat_out[(i * l + k)][j] = NTL::bit(rep(mat_in[i][j]), k)? 1 : 0;
                    }
                }
            }
        }

        void gen_f_prime(CGSW_mat& mat, size_t p, size_t t){
            mat.SetDims(t, t);
            int t_i = t-1;
            // p is normally 2
            for(int i = 0; i < t; i ++){
                for(int j = 0; j < t; j ++){
                    if (t_i < 0) t_i = t-1;
                    mat[i][j] = pow(p, t_i);
                    t_i --;
                }
                t_i ++;
            }
        }

        void gen_f_trapdoor_matrix(CGSW_mat& mat, uint64_t p, uint64_t t){
            // F = H-1 (0)
            // very low rank modulo q
            // small entries
            // full-rank over R but rank 1 over Rq

            // if we were to construct F' as illustrated in the paper, it greatly restrict the option
            // on ciphertext modulus, q, for eg. we can only use q = 17?
            // generate F' ( t x t )
            CGSW_mat f_prime;
            util::gen_f_prime(f_prime, p, t);

            // generate F ( rt x rt ), here r == t
            mat.SetDims(t * t, t * t);
            for (int z = 0; z < t; z ++) {
                for(int i = 0; i < t; i ++ ){
                    for(int j = 0; j < t; j ++){
                        mat[i + z * t][j + z * t] = f_prime[i][j];
                    }
                }
            }
        }

        void gen_h_gadget_matrix(CGSW_mat& mat, uint32_t t){
            // generate F ( rt x rt ), here r == t
            mat.SetDims(t * t, t * t);
            for (int z = 0; z < t; z ++) {
                for(int i = 0; i < t; i ++ ){
                    for(int j = 0; j < t; j ++){
                        mat[i + z * t][j + z * t] = 1;
                    }
                }
            }
        }

    }
}