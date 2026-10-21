#include <stdio.h>

struct Struct {
    char a;
    int b;
    double c;
};

#pragma pack(push, 1)
struct PackedStruct1 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 2)
struct PackedStruct2 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

#pragma pack(push, 4)
struct PackedStruct4 {
    char a;
    int b;
    double c;
};
#pragma pack(pop)

int main() {
    struct Struct d;
    struct PackedStruct1 p1;
    struct PackedStruct2 p2;
    struct PackedStruct4 p4;

    printf("Default Size: %zu bytes\n", sizeof(d));
    printf("Addresses: a=%p, b=%p, c=%p\n", (void*)&d.a, (void*)&d.b, (void*)&d.c);

    printf("\nPack(1) Size: %zu bytes\n", sizeof(p1));
    printf("Addresses: a=%p, b=%p, c=%p\n", (void*)&p1.a, (void*)&p1.b, (void*)&p1.c);

    printf("\nPack(2) Size: %zu bytes\n", sizeof(p2));
    printf("Pack(4) Size: %zu bytes\n", sizeof(p4));

    return 0;
}