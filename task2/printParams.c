#include <stdio.h>

extern char **environ;


int main(int argc, char *argv[]) {
    printf("Number of arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    printf("\nEnvironment Variables:\n");
    for (char **env = environ; *env != 0; env++) {
        printf("%s\n", *env);
    }
    return 0;
}