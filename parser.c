#include <stdio.h>
#include <string.h>
#include <ctype.h>

int parse(char **inputStream, char *parsStr[]) {
    size_t length = strlen(*inputStream);
    char buffer[64];
    int bufferPosition = 0;
    int counter = 0;

    if (length == 0) {
        printf("No value in input stream\n");
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        char c = (*inputStream)[i];

        if (c == ';') {
            parsStr[counter] = strdup(buffer);
            bufferPosition = 0;
            counter++;
            parsStr[counter] = ";";
        }
        else if (isspace(c)) {
            buffer[bufferPosition] = '\0';
            parsStr[counter] = strdup(buffer);
            bufferPosition = 0;
            counter++;
        }
        else if (isalnum(c)) {
            buffer[bufferPosition] = c;
            bufferPosition++;
            buffer[bufferPosition] = '\0';
        }
    }

    return counter;
}
