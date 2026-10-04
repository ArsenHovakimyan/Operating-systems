#include <stdio.h>
#include <stdlib.h>

int main() {

    char **arr = (char **)malloc(3 * sizeof(char *));
    if (arr == NULL) return 1;
    
    for (int i = 0; i < 3; i++) {
        arr[i] = (char *)malloc(50 * sizeof(char));
    }
    
    printf("Enter 3 strings: ");
    for (int i = 0; i < 3; i++) {
        scanf("%49s", arr[i]);
    }
    
    printf("All strings:");
    for (int i = 0; i < 3; i++) {
        printf(" %s", arr[i]);
    }
    printf("\n");
    
    arr = (char **)realloc(arr, 5 * sizeof(char *));
    if (arr == NULL) return 1;
    
    for (int i = 3; i < 5; i++) {
        arr[i] = (char *)malloc(50 * sizeof(char));
    }
    
    printf("Enter 2 more strings: ");
    for (int i = 3; i < 5; i++) {
        scanf("%49s", arr[i]);
    }
    
    printf("All strings:");
    for (int i = 0; i < 5; i++) {
        printf(" %s", arr[i]);
    }
    printf("\n");
    
    for (int i = 0; i < 5; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return 0;
}