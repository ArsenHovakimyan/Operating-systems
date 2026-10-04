#include <stdio.h>
#include <stdlib.h>

int main() {
    int sum = 0;
    int n   = 0;
    
    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;
    
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    
    printf("Sum of the array: %d\n", sum);

    free(arr);
    return 0;
}