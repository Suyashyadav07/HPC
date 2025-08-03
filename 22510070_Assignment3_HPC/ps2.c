#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 2000

void matrix_addition(int n) {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 100;
            B[i][j] = rand() % 100;
        }

    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];

    double end = omp_get_wtime();
    printf("Matrix Size: %d, Threads: %d, Time: %f seconds\n", n, omp_get_max_threads(), end - start);
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    for (int t = 1; t <= 8; t *= 2) {
        omp_set_num_threads(t);
        for (int i = 0; i < 5; i++)
            matrix_addition(sizes[i]);
    }
    return 0;
}
