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

    for (int i = 0; i < len; i++) {
        printf("p: %s \n", parsedTokens[i]);
    }

    for (int i = 0; i < len; i++) {
        char *t =  parsedTokens[i];
        struct Token *newToken = malloc(sizeof(struct Token));

        if (strcmp(t, "return") == 0) {
            newToken->tokenType = _return;
            newToken->value = parsedTokens[i + 1];
            tokens[pos] = newToken;
            i++;
            pos++;
            continue;
        }
        else if(strcmp(t, "int") == 0){
            struct Token *newIdentifierToken = malloc(sizeof(struct Token));
            struct Token *newAssignmentToken = malloc(sizeof(struct Token));
            struct Token *newLiteralToken = malloc(sizeof(struct Token));

            newToken->tokenType = _int;

            newIdentifierToken->tokenType = identifier;
            newIdentifierToken->value = parsedTokens[i+1];

            newAssignmentToken->tokenType = assignment;

            newLiteralToken->tokenType = literal;
            newLiteralToken->value = parsedTokens[i+3];

            if(newIdentifierToken->value == NULL){
                printf("missing identifier");
                return 0;
            }

            if(newLiteralToken->value == NULL){
               newLiteralToken->value = "0";
            }

            tokens[pos++] = newToken;
            tokens[pos++] = newIdentifierToken;
            tokens[pos++] = newAssignmentToken;
            tokens[pos++] = newLiteralToken;

            free(newToken);
            i += 3;
            continue;
        }
        else if (strcmp(parsedTokens[i], ";") == 0) {
            newToken->tokenType = semi;
            newToken->value = NULL;
            tokens[pos] = newToken;
            pos++;
            continue;
        }

        free(newToken);
    }

    for (int i = 0; i < pos; i++) {
        printf("t: %u ", tokens[i]->tokenType);
        printf("t: %s \n", tokens[i]->value);
    }

    return pos;
}