#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    struct Token token1, token2, token3, token4, token5, token6;

    token1.tokenType = _return;
    token1.value = "1";

    token2.tokenType = semi;

    token3.tokenType = _int;

    token4.tokenType = identifier;
    token4.value = "myVar";

    token5.tokenType = assignment;

    token6.tokenType = literal;
    token6.value = "chat";

    struct Token  tokens[99] = {token3, token4, token5, token6, token2, token1, token2};

    char *t = initASM();
    if (strlen(t) == 0) {
        printf("No asm init code");
        return 1;
    }

    unsigned int len = sizeof(tokens) / sizeof(tokens[1]);

    char createdFunctions[len][255];
    char createdVars[len][255];
    int posInFunc = 0;
    int posInVars = 0;

    for(int i = 0; i < len; i++){
        struct Token selectedToken = tokens[i];

        if(selectedToken.tokenType == _return){
            if(tokens[i+1].tokenType != semi){
                printf("Invalid syntax for return statement \n");
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
            continue;
        }

        if(selectedToken.tokenType == _int){
            if (tokens[i + 1].tokenType != identifier || tokens[i + 2].tokenType != assignment || tokens[i + 3].tokenType != literal || tokens[i + 4].tokenType != semi) {
                printf("Invalid syntax for variable declaration\n");
                return 1;
            }

            char *varName = tokens[i + 1].value;
            char *varValue = tokens[i + 3].value;

            char varDecl[512];
            snprintf(varDecl, sizeof(varDecl), "\n %s: .string \"%s\"", varName, varValue);

            strcat(createdVars[posInVars], varDecl);

            posInVars++;
            i += 4;
            continue;
        }
    }

    strcat(t, "_main: \n ");

    for(int i = 0; i < posInFunc; i++){
        char stmt[255];
        sprintf(stmt, "b %s \n", createdFunctions[posInFunc - 1]);
        strcat(t, stmt);
    }

    for(int i = 0; i < posInVars; i++){
        char stmt[255];
        sprintf(stmt, "%s \n", createdVars[posInVars - 1]);
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