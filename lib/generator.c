#include <stdio.h>
#include <string.h>

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

int writer(char *input){
    if(strlen(input) == 0){
        printf("No Input to write");
        return 1;
    }

    FILE *fptr;

    fptr = fopen("../output/output.s", "w");
    fprintf(fptr, "%s", input);
    fprintf(fptr, "_main:\n"
                  "    svc 0\n"
                  "\n");
    fclose(fptr);
    return 0;
}

int generator(){
    char *t = initASM();
    if (strlen(t) == 0) {
        printf("No asm init code");
        return 1;
    }

    writer(t);

    free(t);

    return 0;
}