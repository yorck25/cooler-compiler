#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

    if (readFile(&inputStream) != 0) {
        printf("Error while reading file\n");
        return 1;
    }

    printf("Content of the file: %s\n", inputStream);
    char inputStream[] = "return 0;";

    size_t length = strlen(inputStream);


    //TODO Jonas
    // inputStream => array = ["return", "0", ";"]

    int counter = 0;
    int count = 0;

    char str[3][10];

    for (int i = 0; i < length; i++) {
        if (inputStream[i] == ' ') {
            strncpy (&str[count], &inputStream[counter], i-counter );
            printf("out0: %c\n", inputStream[counter]);
            str[count][i] = '\0';
            counter = i+1;
            count++;
            printf("%i\n", count);
        } else if (inputStream[i] == '0') {
            printf("out0: %c\n", inputStream[counter]);
            strncpy (&str[count][0], &inputStream[counter], 1);
            str[count][i+1] = '\0';
            counter = i+1;
            count++;
            printf("%i\n", count);
        }
        else if (inputStream[i] == ';') {
            printf("out;: %c\n", inputStream[counter]);
            strncpy (&str[count][0], &inputStream[counter], 1);
            str[count][i] = '\0';
            counter = i+1;
            count++;
            printf("%i\n", count);
        }
    }

    printf("str: %s", str[2]);

    return 0;
}
