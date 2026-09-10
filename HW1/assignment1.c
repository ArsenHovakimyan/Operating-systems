#include <stdio.h>

int main() {
    int number = 5;
    int *ptr = &number;

    printf("Address using variable: %p\n", &number);
    printf("Address using pointer:  %p\n", ptr);

    *ptr = 100;
    
    printf("New value of number: %d\n", number);
    return 0;
}