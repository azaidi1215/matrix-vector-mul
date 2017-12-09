#ifndef CLIONPROJECTS_FUNCTIONS_H
#define CLIONPROJECTS_FUNCTIONS_H

#include <iostream>
#include <vector>
using Vector = std::vector<uint64_t>;
using Matrix = std::vector<Vector>;

void init_matrix(Matrix &matrix);

void print_matrix(Matrix &matrix, bool transpose = false);

void init_vector(Vector &vector);

void print_vector(Vector &vector);

void mat_mul_by_rows(Vector &result,
                     Matrix &matrix,
                     Vector &vector,
                     int start_row,
                     int rows_num);

void mat_mul_by_cols(Matrix &sub_results,
                     Matrix &matrix,
                     Vector &vector,
                     int start_col,
                     int cols_num);
#endif //CLIONPROJECTS_FUNCTIONS_H
