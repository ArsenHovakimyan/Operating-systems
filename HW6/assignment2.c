#include <stdio.h>

struct Struct1 {
    char a;
    int b;
    double c;
};

struct Struct2 {
    double c;
    int b;
    char a;
};

struct Struct3 {
    char a;
    double c;
    int b;
};

int main() {
    struct Struct1 s1;
    struct Struct2 s2;
    struct Struct3 s3;

    printf("Original Struct Size: %zu bytes\n", sizeof(s1));
    printf("Address of a (char): %p\n", (void*)&s1.a);
    printf("Address of b (int): %p\n", (void*)&s1.b);
    printf("Address of c (double): %p\n", (void*)&s1.c);

    printf("\nReordered Struct (double, int, char) Size: %zu bytes\n", sizeof(s2));
    printf("Worst-case Struct (char, double, int) Size: %zu bytes\n", sizeof(s3));

    return 0;
}