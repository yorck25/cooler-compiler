#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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