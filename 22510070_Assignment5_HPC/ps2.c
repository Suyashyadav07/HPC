#include <stdio.h>
#include <omp.h>

int main() {
    int m, n, scalar;
    printf("Enter number of rows: ");
    scanf("%d", &m);
    printf("Enter number of columns: ");
    scanf("%d", &n);

    int A[m][n];
    printf("Enter elements of the matrix:\n");
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter scalar value: ");
    scanf("%d", &scalar);

    #pragma omp parallel for collapse(2)
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            A[i][j] *= scalar;

    printf("Resultant Matrix after Scalar Multiplication:\n");
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    return 0;
}
