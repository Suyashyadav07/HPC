#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double sequential_computation(double x) {
    double result;
    double start = omp_get_wtime();

    if (x > 0)
        result = sqrt(x);
    else
        result = log(fabs(x));

    double end = omp_get_wtime();
    printf("\nSequential Execution:\nResult = %.5f, Time = %.2f ms\n",
           result, (end - start) * 1000);
    return (end - start) * 1000; // ms
}

double speculative_computation(double x, int num_threads, double seqTime) {
    double sqrt_result = 0, log_result = 0, final_result = 0;
    double start = omp_get_wtime();

    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp sections
        {
            #pragma omp section
            { sqrt_result = sqrt(fabs(x)); }

            #pragma omp section
            { log_result = log(fabs(x)); }
        }
    }

    if (x > 0)
        final_result = sqrt_result;
    else
        final_result = log_result;

    double end = omp_get_wtime();
    double parTime = (end - start) * 1000; // ms
    double speedup = seqTime / parTime;
    double wasted = (1.0) * 100.0; // since both branches computed, one wasted

    printf("%d\t\t%.2f\t\t%.2f\t%.2f\n", num_threads, parTime, speedup, wasted);
    return parTime;
}

int main() {
    double x;
    printf("Enter the value of x: ");
    scanf("%lf", &x);

    double seqTime = sequential_computation(x);

    printf("\n p threads\tParallelTime(ms)\tSpeedup\tWastedComp(%%)\n");

    int threadsList[] = {2, 4, 8};
    for (int i = 0; i < 3; i++) {
        speculative_computation(x, threadsList[i], seqTime);
    }

    return 0;
}
