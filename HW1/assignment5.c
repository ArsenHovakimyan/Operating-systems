#include <stdio.h>

int main() {
    char str[] = "Hello";
    char *ptr = str;
    int count = 0;

    while (*ptr != '\0') {
        printf("%c", *ptr);
        ptr++;
        count++;
    }
    
    printf("\nNumber of characters: %d\n", count);
    return 0;
}