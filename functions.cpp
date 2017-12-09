#include "functions.h"

/**
 * Multiply matrix and vector. Matrix is stored by rows.
 *
 * @param result
 * @param matrix
 * @param vector
 * @param start_row index of row to start from
 * @param rows_num number of rows to process
 */
void mat_mul_by_rows(Vector &result,
                     Matrix &matrix,
                     Vector &vector,
                     int start_row,
                     int rows_num) {

    uint64_t sub_result;
    for (int ii = start_row; ii < start_row + rows_num; ++ii) {
        sub_result = 0;
        for (int jj = 0; jj < vector.size(); ++jj) {
            sub_result += matrix[ii][jj] * vector[jj];
        }
        result[ii] = sub_result;
    }
}

/**
 * Multiply matrix and vector. Matrix is stored by columns.
 *
 * @param sub_results
 * @param matrix
 * @param vector
 * @param start_col index of row to start from
 * @param cols_num number of rows to process
 */
void mat_mul_by_cols(Matrix &sub_results,
                     Matrix &matrix,
                     Vector &vector,
                     int start_col,
                     int cols_num) {

    std::vector<uint64_t> sub_vector(vector.size());
    for (int ii = 0; ii < vector.size(); ++ii) {
        sub_vector[ii] = 0;
        for (int jj = start_col; jj < start_col + cols_num; ++jj) {
            sub_vector[ii] += matrix[jj][ii] * vector[jj];
        }
    }
    sub_results.push_back(sub_vector);
}

/**
 * Initialize matrix with values from 0 to 99.
 *
 * @param matrix
 */
void init_matrix(Matrix &matrix) {
    for (auto &vector : matrix) {
        for (auto &i : vector) {
            i = rand() % 100;
        }
    }
}

/**
 * Initialize vector with values from 0 to 99.
 *
 * @param vector
 */
void init_vector(Vector &vector) {
    for (uint64_t &i : vector) {
        i = rand() % 100;
    }
}

/**
 * Print matrix.
 *
 * @param matrix
 * @param transpose
 */
void print_matrix(Matrix &matrix, bool transpose) {
    uint64_t outer_loop_limit, inner_loop_limit;
    if (transpose) {
        outer_loop_limit = matrix[0].size();
        inner_loop_limit = matrix.size();
    } else {
        outer_loop_limit = matrix.size();
        inner_loop_limit = matrix[0].size();
    }
    for (int i = 0; i < outer_loop_limit; ++i) {
        for (int j = 0; j < inner_loop_limit; ++j) {
            if (transpose) {
                std::cout << matrix[j][i] << ' ';
            } else {
                std::cout << matrix[i][j] << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

/**
 * Print vector.
 *
 * @param vector
 */
void print_vector(Vector &vector) {
    for (auto &i : vector) {
        std::cout << i << '\n';
    }
    std::cout << std::endl;
}
