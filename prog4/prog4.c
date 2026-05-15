#include <stdio.h>
#include <stdint.h>

// Define a structure with bitfields
struct Bitfield {
    uint8_t firstbit  : 1;  // Uses 1 bit (values 0 or 1)
    uint8_t middlebits : 3;  // Uses 3 bits (values 0 to 7)
    uint8_t lastbits   : 4;  // Uses 4 bits (values 0 to 15)
};
int main() {
    // 1. Declaration
    struct Bitfield a;

    // 2. Assignment
    a.firstbit = 2;      // Setting the 1st bit
    a.middlebits = 5;    // Binary 101
    a.lastbits = 10;     // Binary 1010

    // 3. Testing/Verification
    printf("--- Bitfield Values ---\n");
    printf("First bit:  %u\n", a.firstbit);
    printf("Middle:     %u\n", a.middlebits);
    printf("Last:       %u\n", a.lastbits);
    
    // 4. Memory Size Check
    printf("\n--- Memory Analysis ---\n");
    printf("Size of struct: %zu byte(s)\n", sizeof(a));

    return 0;
}