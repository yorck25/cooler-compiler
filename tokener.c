#include <stdio.h>

struct Token {
    char type[20];
    int value;
};

int token() {
    struct Token tokens;

    strcpy(tokens.type, "token");
    tokens.value = 0;

    printf("%s\n", tokens.type);
    printf("%d\n", tokens.value);

    return 0;
}