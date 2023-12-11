#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int detectAmount(const char* color, char* string) {
    char* wordpos = strstr(string, color);
    if (wordpos == NULL) return 0;
    int offset = wordpos-string;
    int i;
    for (i = offset-2;i>=0;i--) {
        if (string[i] == ' ') break;
    }
    char atoip[10];
    strncpy(atoip, string+offset-2, offset-i-1);
    return atoi(atoip);
}

int hasValidNumbers(char* game) {
    printf("Analyzing: %s\n", game);
    char* pch = strtok(game, ";");
    int redamount, greenamount, blueamount;
    while (pch != NULL) {
        redamount = detectAmount("red", pch);
        greenamount = detectAmount("green", pch);
        blueamount = detectAmount("blue", pch);
        printf("Detected %d red, %d green, %d blue\n", redamount, greenamount, blueamount);
        if (redamount > 12) {
            return 0;
        }
        if (greenamount > 13) {
            return 0;
        }
        if (blueamount > 14) {
            return 0;
        }
        pch = strtok(NULL, ";");
    }
    return 1;
}

int* replaceNewline(char* input, size_t size, int *returnval) {
    *returnval = 1;
    for (int iterator = 0;iterator<size;iterator++) {
        if (input[iterator] == '\n') {
            (*returnval)++;
        } 
    }
    int *array = calloc(*returnval, sizeof(int));
    array[0] = 0;
    int moreiterators = 1;
    for (int iterator = 0;iterator<size;iterator++) {
        if (input[iterator] == '\n') {
            input[iterator] = '\0';
            array[moreiterators] = iterator+1;
            moreiterators++;
        } 
    }
    return array;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Ayo why you forget to provide txt with input??\n");
        return 0;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Nice file you have there but its not fine\n");
        return 0;
    }
    fseek(file, 0, SEEK_END);
    int size = ftell(file);

    char* sbuf = malloc(size);

    fseek(file, 0, SEEK_SET);
    fread(sbuf, 1, size, file);
    fclose(file);
    printf("file size: %d\n", size);
    size_t ssize = strlen(sbuf);
    printf("strlen: %d\n", ssize);

    int finalval = 0;
    
    int lines;
    int *linelist = replaceNewline(sbuf, ssize, &lines);
    lines = 4;
    printf("Lines: %d\n", lines);
    for (int i = 1;i<lines+1;i++) {
        if (hasValidNumbers(sbuf+linelist[i-1])) {
            printf("Valid\n");
            finalval += i;
        }
    }

    printf("result: %d\n", finalval);
    free(linelist);
    free(sbuf);
    return 0;
}