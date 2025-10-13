#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAXN 15

int isSafe(int board[MAXN], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    }
    return 1;
}

int solveNQueens(int board[MAXN], int row, int N) {
    if (row == N) return 1;

    int count = 0;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            count += solveNQueens(board, row + 1, N);
        }
    }
    return count;
}

int solveNQueensParallel(int N, int num_threads) {
    int totalSolutions = 0;
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic) reduction(+:totalSolutions) num_threads(num_threads)
    for (int col = 0; col < N; col++) {
        int board[MAXN];
        board[0] = col;
        totalSolutions += solveNQueens(board, 1, N);
    }

    double end = omp_get_wtime();
    double parallelTime = (end - start) * 1000; // ms
    printf("%d\t\t%.2f\t\t", num_threads, parallelTime);
    return totalSolutions;
}

int main() {
    int N;
    printf("Enter the value of N: ");
    scanf("%d", &N);

    int board[MAXN];
    double start_seq = omp_get_wtime();
    int seqSolutions = solveNQueens(board, 0, N);
    double end_seq = omp_get_wtime();
    double seqTime = (end_seq - start_seq) * 1000; // ms

    printf("\nSequential Execution:\n");
    printf("Solutions = %d, Time = %.2f ms\n", seqSolutions, seqTime);

    printf("\n p threads\tParallelTime(ms)\tSpeedup\tWastedComp(%%)\n");

    int threadsList[] = {2, 4, 8};
    for (int i = 0; i < 3; i++) {
        int p = threadsList[i];
        double start = omp_get_wtime();
        int parSolutions = solveNQueensParallel(N, p);
        double end = omp_get_wtime();
        double parTime = (end - start) * 1000;

        double speedup = seqTime / parTime;
        double wasted = ((double)(parSolutions - seqSolutions) / seqSolutions) * 100.0;
        printf("%.2f\t%.2f\n", speedup, wasted);
    }

    return 0;
}
