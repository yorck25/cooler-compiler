#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readFile(char **inputStream) {
    int bufferSize = 100;
    int lineBufferSize = 80;

    FILE *inputFile = fopen("../input.txt", "r");
    if (inputFile == NULL) {
        printf("Unable to open the file\n");
        return 1;
    }

    *inputStream = (char *)malloc(bufferSize * sizeof(char));
    if (*inputStream == NULL) {
        printf("Memory allocation failed\n");
        fclose(inputFile);
        return 1;
    }
    (*inputStream)[0] = '\0';

    char *lineBuffer = (char *)malloc(lineBufferSize * sizeof(char));
    if (lineBuffer == NULL) {
        printf("Memory allocation for line buffer failed\n");
        free(*inputStream);
        fclose(inputFile);
        return 1;
    }

    while (fgets(lineBuffer, lineBufferSize, inputFile) != NULL) {
        if (strlen(*inputStream) + strlen(lineBuffer) + 1 > bufferSize) {
            bufferSize *= 2;
            char *temp = realloc(*inputStream, bufferSize * sizeof(char));
            if (temp == NULL) {
                printf("Memory reallocation failed\n");
                free(*inputStream);
                free(lineBuffer);
                fclose(inputFile);
                return 1;
            }
            *inputStream = temp;
        }

        strcat(*inputStream, lineBuffer);
    }

    free(lineBuffer);
    fclose(inputFile);

    return 0;
}