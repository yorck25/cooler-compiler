#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum TokenType {
    semi,
    _int,
    _return,
};

struct Token {
    enum TokenType tokenType;
    char *value;
};

char *initASM() {
    char *line1 = ".globl _main\n";
    char *line2 = ".align 2\n";
    char *line3 = "\n";

    unsigned int totalLength = strlen(line1) + strlen(line2) + strlen(line3) + 1;

    char *result = malloc(totalLength * sizeof(char));
    if (result == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strcpy(result, line1);
    strcat(result, line2);
    strcat(result, line3);

    return result;
}

int writer(char *input) {
    if (strlen(input) == 0) {
        printf("No Input to write");
        return 1;
    }

    FILE *fptr;

    fptr = fopen("../output/output.s", "w");
    fprintf(fptr, "%s", input);
    fclose(fptr);
    return 0;
}

int generator() {
    //just demo tokens
    //TODO implement that tokens get passed as params
    //-------
    struct Token token1;
    struct Token token2;
    token1.tokenType = _return;
    token1.value = "1";
    token2.tokenType = semi;
    struct Token tokens[2] = {token1, token2};

    char *t = initASM();
    if (strlen(t) == 0) {
        printf("No asm init code");
        return 1;
    }

    unsigned int len = sizeof(tokens) / sizeof(tokens[1]);

    char createdFunctions[len][255];
    int posInFunc = 0;

    for(int i = 0; i < len; i++){
        struct Token selectedToken = tokens[i];

        if(selectedToken.tokenType == _return){
            if(tokens[i+1].tokenType != semi){
                printf("missing semi after return statement. \n");
                return 1;
            }

            char func_name[255];
            snprintf(func_name, 255, "function_%d_%d", selectedToken.tokenType, i);

            char _returnStmt[512];
            sprintf(_returnStmt, "%s: \n mov X0, #%s \n mov X16, #1 \n svc 0 \n\n", func_name, selectedToken.value);

            strcat(t, _returnStmt);

            strcpy(createdFunctions[posInFunc], func_name);
            posInFunc++;
            i++;
        }
    }

    strcat(t, "_main: \n ");

    for(int i = 0; i < posInFunc; i++){
        char stmt[255];
        sprintf(stmt, "b %s \n", createdFunctions[posInFunc - 1]);
        strcat(t, stmt);
    }

    if(writer(t) != 0){
        printf("fail to write asm \n");
        free(t);
        return 1;
    }

    free(t);

    return 0;
}