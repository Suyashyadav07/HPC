#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d",&n);

    int arr[n], prefix[n];
    printf("Enter elements:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&arr[i]);

    double start = omp_get_wtime();
    prefix[0] = arr[0];
    #pragma omp parallel for
    for(int i=1;i<n;i++)
        prefix[i] = prefix[i-1] + arr[i];
    double end = omp_get_wtime();

    printf("Prefix Sum Array:\n");
    for(int i=0;i<n;i++)
        printf("%d ",prefix[i]);
    printf("\n");

    printf("Time Taken: %f seconds\n", end-start);
    return 0;
}
