#include <stdio.h>

int main() {
    int value = 10;
    int *ptr = &value;
    int **dPtr = &ptr;

    printf("Value using pointer: %d\n", *ptr);
    printf("Value using double-pointer: %d\n", **dPtr);

    return 0;
}