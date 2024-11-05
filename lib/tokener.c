#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TokenType {
    semi,
    _return,
    _int,
    identifier,
    assignment,
    literal
};

struct Token {
    enum TokenType tokenType;
    char *value;
};

int tokenizer(char *parsedTokens[], int len, struct Token *tokens[]) {
    int pos = 0;

    for (int i = 0; i < len + 1; i++) {
        struct Token *newToken = malloc(sizeof(struct Token));
        printf("p: %s \n", parsedTokens[i]);

        if (strcmp(parsedTokens[i], "return") == 0) {
            newToken->tokenType = _return;
            newToken->value = parsedTokens[i + 1];
            tokens[pos] = newToken;
            i++;
            pos++;
            continue;
        }

        if (strcmp(parsedTokens[i], ";") == 0) {
            newToken->tokenType = semi;
            newToken->value = NULL;
            tokens[pos] = newToken;
            pos++;
            continue;
        }
    }

    for (int i = 0; i < pos; i++) {
        printf("t: %u \n", tokens[i]->tokenType);
    }

    return pos;
}