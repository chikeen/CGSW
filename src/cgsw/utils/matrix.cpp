//
// Created by Chi Keen Tan on 02/02/2021.
//

#include "../../../include/cgsw/utils/matrix.h"

std::random_device rd;
std::mt19937 generator(rd());

namespace cgsw {
    namespace util{

        void gen_random_matrix(CGSW_mat& mat, size_t n, size_t m) {
            NTL::random(mat, n, m);
        }

        void gen_random_matrix(CGSW_mat& mat, size_t n, size_t m, size_t limit) {
            mat.SetDims(n, m);
            for (int i = 0; i < n; i ++){
                for (int j = 0; j < m; j ++){
                    mat[i][j] = NTL::RandomBnd(limit);
                }
            }
        }

        void gen_empty_matrix(CGSW_mat& mat, size_t n, size_t m){
            mat.SetDims(n, m);
        }

        void gen_identity_matrix(CGSW_mat& mat, size_t n, size_t m){
            mat.SetDims(n, m);
            assert(n == m);

            for (int i = 0; i < n; i ++){
                mat[i][i] = 1;
            }
        }

        void gen_normal_matrix(CGSW_mat& mat, size_t n, size_t m){
            mat.SetDims(n, m);
            const CGSW_long modulus = CGSW_mod::modulus();
            const int mean(0);
            const double stddev(0);// TODO:- how to calculate the standard deviation?
            //TODO:- temperorary setting stddev to 0 meaning no noise

            mat.SetDims(n, m);

            // Since the normal distribution matrix centered around 0, can use int instead of NTL:ZZ
            std::normal_distribution<double> distribution(mean, stddev);
            double random_num;

            for(int i = 0; i < n; i ++){
                for(int j = 0; j < m; j ++){
                    random_num = distribution(generator);
                    if (random_num < 0) {random_num = -random_num;}
                    mat[i][j] =  (CGSW_mod) random_num; // no need to modulus since its small?
                }
            }

//            std::cout << "noise matrix: \n" << mat << std::endl;
        }

        void gen_gadget_matrix(CGSW_mat& mat, size_t n, size_t m){
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

        void gen_random_uint_matrix(CGSW_mat_uint& mat,  size_t n, size_t m, size_t range){

            mat.SetDims(n, m);
            std::uniform_int_distribution<uint64_t> distribution(0, range-1);

            for(int i = 0; i < n; i ++){
                for(int j = 0; j < m; j ++){
                    mat[i][j] = (uint64_t) distribution(generator);
                }
            }
        }

        void concat_matrix_h(CGSW_mat& mat_out, const CGSW_mat& mat_a, const CGSW_mat& mat_b){

            auto a_rows = mat_a.NumRows(),
                a_cols = mat_a.NumCols(),
                b_rows = mat_b.NumRows(),
                b_cols = mat_b.NumCols();

            assert(a_rows == b_rows);
            mat_out.SetDims(a_rows, a_cols + b_cols);

            for(int i = 0; i < a_rows; i ++){
                for (int j = 0; j < a_cols; j++){
                    mat_out[i][j] = mat_a[i][j];
                }
            }

            for(int i = 0; i < b_rows; i ++){
                for (int j = 0; j < b_cols; j++){
                    mat_out[i][j + a_cols] = mat_b[i][j];
                }
            }
        }

        void concat_matrix_h(CGSW_mat& mat_out, const CGSW_mat& mat_a, const CGSW_vec& vec_b){
            throw(NotImplemented());
        }

        void concat_matrix_v(CGSW_mat& mat_out, const CGSW_mat& mat_a, const CGSW_mat& mat_b){

            auto a_rows = mat_a.NumRows(),
                    a_cols = mat_a.NumCols(),
                    b_rows = mat_b.NumRows(),
                    b_cols = mat_b.NumCols();

            assert(a_cols == b_cols);
            mat_out.SetDims(a_rows + b_rows, a_cols);

            for(int i = 0; i < a_rows; i ++){
                for (int j = 0; j < a_cols; j++){
                    mat_out[i][j] = mat_a[i][j];
                }
            }

            for(int i = 0; i < b_rows; i ++){
                for (int j = 0; j < b_cols; j++){
                    mat_out[i + a_rows][j] = mat_b[i][j];
                }
            }
        }

        CGSW_mod get_norm(const CGSW_mat& mat){
            CGSW_mod acc(0);
            for(long m  = 0; m < mat.NumRows(); m ++){
                for(long n = 0; n < mat.NumCols(); n ++){
                    acc += mat[m][n] * mat[m][n];
                }
            }
            return acc;
        }

        CGSW_mod get_norm(const CGSW_vec& vec){
            CGSW_mod acc(0);
            for(long i  = 0; i < vec.length(); i ++){
                acc += vec[i] * vec[i];
            }
            return acc;
        }

        CGSW_long get_sum(const CGSW_mat& mat){
            CGSW_long acc(0);
            for(long m  = 0; m < mat.NumRows(); m ++){
                for(long n = 0; n < mat.NumCols(); n ++){
                    acc += rep(mat[m][n]);
                }
            }
            return acc;
        }


    } // util
} // cgsw
