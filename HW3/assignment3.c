#include <stdio.h>
#include <stdlib.h>

void function_one() {
    printf("Function 1 executed.\n");
}

void function_two() {
    printf("Function 2 executed.\n");
}

int main() {
    atexit(function_one);
    atexit(function_two);

    printf("Program running...\n");
    exit(0);
}