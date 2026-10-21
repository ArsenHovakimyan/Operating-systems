#include <stdio.h>

int main() {
    int    var_int;
    char   var_char;
    double var_double;
    short  var_short;

    printf("Sizes:\n");
    printf("int: %zu bytes\n", sizeof(var_int));
    printf("char: %zu bytes\n", sizeof(var_char));
    printf("double: %zu bytes\n", sizeof(var_double));
    printf("short: %zu bytes\n", sizeof(var_short));

    printf("\nAddresses:\n");
    printf("int: %p\n", (void*)&var_int);
    printf("char: %p\n", (void*)&var_char);
    printf("double: %p\n", (void*)&var_double);
    printf("short: %p\n", (void*)&var_short);

    return 0;
}