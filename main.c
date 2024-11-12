#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib/reader.c"
#include "lib/parser.c"
#include "lib/tokener.c"
#include "lib/generator.c"

int main() {
    char *inputStream = NULL;
    char *parsedTokens[255];

    if (readFile(&inputStream) != 0) {
        printf("Error while reading file\n");
        return 1;
    }

    const int parsedCount = parse(&inputStream, parsedTokens);
    if (parsedCount == 0) {
        printf("No tokens were passed back from parser\n");
        return 1;
    }

    struct Token *tokens[parsedCount];

    const int tokenizedCount = tokenizer(parsedTokens, parsedCount, tokens);
    if (tokenizedCount == 0) {
        printf("No tokens were passed back from tokenizer\n");
        return 1;
    }

    if(generator(tokens) != 0){
        printf("!! Failed to generate asm !!");
        return 1;
    }

    system("chmod +x ../scripts/compile.sh");
    system("../scripts/compile.sh");

    return 0;
}