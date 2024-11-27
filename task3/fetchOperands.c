#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  



int main(int argc, char *argv[]) {


    char *operator = getenv("OPERATOR");
    int result = 0;
    if (operator == NULL) {
        printf("Environment variable OPERATOR is not set.\n");
        return 1;
    }
    printf("Operator: %s\n", operator);
    if(strcmp(operator, "add") == 0){
        for(int i = 1; i < argc; i++){
            result += atoi(argv[i]);
        }
    }

    if(strcmp(operator, "mult") == 0){
        result = 1;
        for(int i = 1; i < argc; i++){
            result *= atoi(argv[i]);
        }
    }

    printf("Result: %d\n", result);
    return 0;
}

