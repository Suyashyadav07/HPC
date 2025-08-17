#include <stdio.h>
#include <omp.h>

int main() {
    int m, n;
    printf("Enter number of rows of matrix: ");
    scanf("%d", &m);
    printf("Enter number of columns of matrix / size of vector: ");
    scanf("%d", &n);

    int A[m][n], V[n], R[m];

    printf("Enter elements of matrix (A):\n");
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of vector (V):\n");
    for(int i=0; i<n; i++)
        scanf("%d", &V[i]);

    #pragma omp parallel for
    for(int i=0; i<m; i++) {
        R[i] = 0;
        for(int j=0; j<n; j++) {
            R[i] += A[i][j] * V[j];
        }
    }

    printf("Resultant Vector (R = A x V):\n");
    for(int i=0; i<m; i++)
        printf("%d\n", R[i]);

    return 0;
}
