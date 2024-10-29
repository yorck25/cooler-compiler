#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.c"

int readFile(char **inputStream) {
    FILE *inputFile;
    inputFile = fopen("../input.txt", "r");

    if (inputFile == NULL) {
        printf("Not able to open the file\n");
        return 1;
    }

    *inputStream = (char *) malloc(100 * sizeof(char));
    if (*inputStream == NULL) {
        printf("Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }

    if (fgets(*inputStream, 100, inputFile) == NULL) {
        printf("Error reading from file\n");
        fclose(inputFile);
        free(*inputStream);
        return 1;
    }

    fclose(inputFile);
    return 0;
}

int generator() {
    FILE *fptr;

    fptr = fopen("../output/output.s", "w");

    fprintf(fptr, ".globl _main\n"
                  ".align 2\n"
                  "\n"
                  "_main:\n"
                  "    b _terminate\n"
                  "\n"
                  "_printf:\n"
                  "    mov X0, #1 // stdout\n"
                  "    adr X1, helloworld // address of string\n"
                  "    mov X2, #12 // length of string\n"
                  "    mov X16, #4 // write to stdout\n"
                  "    svc 0    // syscall\n"
                  "\n"
                  "_terminate:\n"
                  "    mov X0, #69 // return 0\n"
                  "    mov X16, #1 // terminate\n"
                  "    svc 0    // syscall\n"
                  "\n"
                  "helloworld: .asciz \"Hello, world\" \n");

    fclose(fptr);

    return 0;
}

int main() {
    char *inputStream = NULL;
    char *parsedTokens[255];

    if (readFile(&inputStream) != 0) {
        printf("Error while reading file\n");
        return 1;
    }

    printf("Content of the file: %s\n", inputStream);

    const int parsedCount = parse(&inputStream, parsedTokens);
    if (parsedCount == 0) {
        printf("No tokens were passed back\n");
        return 1;
    }

    for (int i = 0; i < parsedCount + 1; i++) {
        printf("%s \n", parsedTokens[i]);
    }

    generator();

    system("chmod +x ../scripts/compile.sh");
    system("../scripts/compile.sh");

    return 0;
}