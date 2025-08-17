#include <stdio.h>
#include <omp.h>

int main() {
    int m, n, p;
    printf("Enter rows of first matrix: ");
    scanf("%d", &m);
    printf("Enter columns of first matrix / rows of second matrix: ");
    scanf("%d", &n);
    printf("Enter columns of second matrix: ");
    scanf("%d", &p);

    int A[m][n], B[n][p], C[m][p];

    printf("Enter elements of first matrix (A):\n");
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of second matrix (B):\n");
    for(int i=0; i<n; i++)
        for(int j=0; j<p; j++)
            scanf("%d", &B[i][j]);

    // Initialize result
    for(int i=0; i<m; i++)
        for(int j=0; j<p; j++)
            C[i][j] = 0;

    #pragma omp parallel for collapse(2)
    for(int i=0; i<m; i++) {
        for(int j=0; j<p; j++) {
            for(int k=0; k<n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("Resultant Matrix (C = A x B):\n");
    for(int i=0; i<m; i++) {
        for(int j=0; j<p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
