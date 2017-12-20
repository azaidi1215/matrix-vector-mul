#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include "functions.h"

const int ROWS = 150, COLS = 300;
const int THREADS_TO_USE = 2;

void test_by_rows() {
    assert(ROWS >= THREADS_TO_USE);

    Matrix matrix(ROWS, Vector(COLS));
    Vector vector(COLS);
    Vector result_vector(ROWS);

    srand(time(0));
    init_matrix(matrix);
    init_vector(vector);
//    print_matrix(matrix);
//    print_vector(vector);

    std::vector<std::thread *> threads;
    int rows_per_thread = ROWS / THREADS_TO_USE;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ROWS; i += rows_per_thread) {

        if (i + 2 * rows_per_thread > ROWS) {
            rows_per_thread = ROWS - i;
        }

        threads.push_back(new std::thread(std::bind(mat_mul_by_rows,
                                                    std::ref(result_vector),
                                                    matrix,
                                                    vector,
                                                    i,
                                                    rows_per_thread)));
    }
    for (int j = 0; j < THREADS_TO_USE; j++) {
        threads[j]->join();
    }
    auto end = std::chrono::high_resolution_clock::now();

//    print_vector(result_vector);
    double timeTakenInSeconds = (end - start).count()
                                * ((double) std::chrono::high_resolution_clock::period::num
                                   / std::chrono::high_resolution_clock::period::den);
    printf("Time, s: %lf", timeTakenInSeconds);

    for (int h = 0; h < THREADS_TO_USE; h++) {
        delete threads[h];
    }
}

void test_by_cols() {
    assert(COLS >= THREADS_TO_USE);

    Matrix matrix_by_cols(COLS, Vector(ROWS));
    Vector vector(COLS);
    Matrix sub_results; // actually it's vector of {result vectors of each thread}
    Vector result_vector(ROWS, 0);

    srand(time(0));
    init_matrix(matrix_by_cols);
    init_vector(vector);
//    print_matrix(matrix_by_cols, true);
    print_vector(vector);

    std::vector<std::thread *> threads;
    int cols_per_thread = COLS / THREADS_TO_USE;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < COLS; i += cols_per_thread) {
        if (i + 2 * cols_per_thread > COLS) {
            cols_per_thread = COLS - i;
        }
        threads.push_back(new std::thread(std::bind(mat_mul_by_cols,
                                                    std::ref(sub_results),
                                                    matrix_by_cols,
                                                    vector,
                                                    i,
                                                    cols_per_thread)));
    }
    for (int j = 0; j < THREADS_TO_USE; j++) {
        threads[j]->join();
    }

    for (int k = 0; k < ROWS; ++k) {
        for (int l = 0; l < sub_results.size(); ++l) {
            result_vector[k] += sub_results[l][k];
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

//    print_vector(result_vector);
    double timeTakenInSeconds = (end - start).count()
                                * ((double) std::chrono::high_resolution_clock::period::num
                                   / std::chrono::high_resolution_clock::period::den);
    printf("Time, s: %lf", timeTakenInSeconds);

    for (int h = 0; h < THREADS_TO_USE; h++) {
        delete threads[h];
    }
}

int main() {
//    test_by_rows();
    test_by_cols();

    return 0;
}
