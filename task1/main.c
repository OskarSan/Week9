#include <stdio.h>
#include <stdlib.h>
#include "sum.h"


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    int numOne = atoi(argv[1]);
    int numTwo = atoi(argv[2]);

    printf("Sum of %d and %d is %d\n", 
    numOne, numTwo, sum(numOne, numTwo));

    return 0;
}