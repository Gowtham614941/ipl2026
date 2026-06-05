#include <stdio.h>


 
void printBits(int n) 
{
    for (int i = 31; i >= 0; i--) 
    {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        if (i % 8 == 0) printf(" "); // Formatting: space between bytes
    }
}


int countSetBits(int n) 
{
    int count = 0;
    unsigned int un = (unsigned int)n; // Cast to unsigned to handle negatives safely
    while (un != 0) 
    {
        un &= (un - 1);
        count++;
    }
    return count;
}


int main() {
    int posInt,negInt;
    printf("Enter a positive number");
    scanf("%d",&posInt);
    printf("Enter a negative number");
    scanf("%d",&negInt);
    printf("Pos  %d: ",posInt); 
    printBits(posInt); 
    printf(" (Set bits: %d)\n", countSetBits(posInt));
    
    printf("Neg %d: ",negInt); 
    printBits(negInt); 
    printf(" (Notice the leading 1s)\n");
    return 0;
}