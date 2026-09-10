#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr; 

    printf("Array values:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    printf("\n");

    for (int i = 0; i < 5; i++) {
        *(ptr + i) += 10; 
    }

    printf("Modified array using pointer: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr + i));
    }
    
    printf("\nModified array using array name: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}