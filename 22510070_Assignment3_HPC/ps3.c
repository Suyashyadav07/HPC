#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 200  // Vector size

void initialize_vector(float *a, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = i * 1.0f;
    }
}

void print_vector(float *vec, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.2f ", vec[i]);
    }
    printf("\n");
}

void vector_scalar_add_static(float *a, float scalar, float *c, int size, int chunk) {
    #pragma omp parallel for schedule(static, chunk)
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + scalar;
    }
}

void vector_scalar_add_dynamic(float *a, float scalar, float *c, int size, int chunk) {
    #pragma omp parallel for schedule(dynamic, chunk)
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + scalar;
    }
}

void vector_scalar_add_nowait(float *a, float scalar, float *c, int size, int chunk) {
    #pragma omp parallel
    {
        #pragma omp for schedule(static, chunk) nowait
        for (int i = 0; i < size; i++) {
            c[i] = a[i] + scalar;
        }
        // no barrier here due to nowait
        #pragma omp single
        {
            printf("nowait clause used — other threads don't wait for loop to complete.\n");
        }
    }
}

int main() {
    float a[SIZE], c[SIZE];
    float scalar = 5.0;
    int chunk_sizes[] = {1, 5, 10, 20, 50}; // For analysis
    int num_threads;

    initialize_vector(a, SIZE);

    printf("Enter number of threads: ");
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);

    for (int i = 0; i < 5; i++) {
        int chunk = chunk_sizes[i];

        // ---- STATIC ----
        double start_static = omp_get_wtime();
        vector_scalar_add_static(a, scalar, c, SIZE, chunk);
        double end_static = omp_get_wtime();
        printf("\n[STATIC] Chunk: %d | Time: %f sec\n", chunk, end_static - start_static);

        // ---- DYNAMIC ----
        double start_dynamic = omp_get_wtime();
        vector_scalar_add_dynamic(a, scalar, c, SIZE, chunk);
        double end_dynamic = omp_get_wtime();
        printf("[DYNAMIC] Chunk: %d | Time: %f sec\n", chunk, end_dynamic - start_dynamic);
    }

    // ---- NOWAIT DEMO ----
    printf("\n[NOWAIT CLAUSE DEMO]\n");
    vector_scalar_add_nowait(a, scalar, c, SIZE, 10);

    return 0;
}
