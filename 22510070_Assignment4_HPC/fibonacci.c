#include <stdio.h>
#include <omp.h>

// Recursive Fibonacci with OpenMP tasks
long long fibonacci(int n) {
    if (n < 2)
        return n;

    long long x, y;

    #pragma omp task shared(x)
    x = fibonacci(n - 1);

    #pragma omp task shared(y)
    y = fibonacci(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n;
    printf("Enter N: ");
    scanf("%d", &n);

    long long fib[n];

    double start = omp_get_wtime();

    // Start parallel region
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < n; i++) {
                fib[i] = fibonacci(i);
            }
        }
    }

    double end = omp_get_wtime();

    // Print series
    printf("Fibonacci series up to %d terms:\n", n);
    for (int i = 0; i < n; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");

    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
