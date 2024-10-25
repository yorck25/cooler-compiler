#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.c"

int readFile(char **inputStream) {
    FILE *inputFile;
    inputFile = fopen("input.txt", "r");

    if (inputFile == NULL) {
        printf("Not able to open the file\n");
        return 1;
    }

    *inputStream = (char *)malloc(100 * sizeof(char));
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

int main() {
    char *inputStream = NULL;
    char *parsedTokens[255];

    if (readFile(&inputStream) != 0) {
        printf("Error while reading file\n");
        return 1;
    }

    printf("Content of the file: %s\n", inputStream);

    const int parsedCount = parse(&inputStream, parsedTokens);
    if(parsedCount == 0){
        printf("No tokens were passed back\n");
        return 1;
    }

    for(int i = 0; i < parsedCount + 1; i++){
        printf("%s \n", parsedTokens[i]);
    }

    return 0;
}