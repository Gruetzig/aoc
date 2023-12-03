#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hasNumberAtOffset(char* stringpointer, int offset, int stringsize) {
    if (stringsize - offset+ 3 >= 0) //one two six
        {
            if (strncmp(stringpointer+offset, "one", 3) == 0) return 1;
            if (strncmp(stringpointer+offset, "two", 3) == 0) return 2;
            if (strncmp(stringpointer+offset, "six", 3) == 0) return 6;
        }
    if (stringsize - offset+ 4 >= 0) //four five nine
        {
            if (strncmp(stringpointer+offset, "four", 4) == 0) return 4;
            if (strncmp(stringpointer+offset, "five", 4) == 0) return 5;
            if (strncmp(stringpointer+offset, "nine", 4) == 0) return 9;
        }
    if (stringsize - offset+ 5 >= 0) //three seven eight
        {
            if (strncmp(stringpointer+offset, "three", 5) == 0) return 3;
            if (strncmp(stringpointer+offset, "seven", 5) == 0) return 7;
            if (strncmp(stringpointer+offset, "eight", 5) == 0) return 8;
        }
    return 0;

        
}

int getnumber(char* thing, size_t size, int shouldDoWords) {
    int ret = 0;
    int tempval = 0;
    for (int i = 0;i < size;i++) {
        if (shouldDoWords) {
            tempval = hasNumberAtOffset(thing, i, size);
            if (tempval) {
                ret += tempval*10;
                break;
            }
        }
        if (thing[i] >= '0' && thing[i] <= '9') {
            ret += (thing[i] - '0')*10;
            //printf("getnumber: string: %s char: %c first number: %d\n", thing, thing[i], ret);
            break;
        } 
    }
    for (int i = size;i >= 0;i--) {
        if (shouldDoWords) {
            tempval = hasNumberAtOffset(thing, i, size);
            if (tempval) {
                ret += tempval;
                break;
            }
        }
        if (thing[i] >= '0' && thing[i] <= '9') {
            ret += thing[i] - '0';
            //printf("getnumber: string: %s char: %c second number: %d\n", thing, thing[i], thing[i] - '0');
            break;
        } 
    }
    return ret;
}

int main(int argc, char* argv[]) {
    int shouldDoWords;
    if (argc == 3) shouldDoWords = 1;
    else if (argc != 2) {
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
    int finalval = 0;
    printf("file size: %d\n", size);
    printf("strlen: %d\n", strlen(sbuf));
    char* pch = strtok(sbuf, "\n");
    while(pch != NULL) {
        int curlen = strlen(pch);
        int curval = getnumber(pch, curlen, shouldDoWords);
        finalval += curval;
        printf("finalval: %d pch: %s curval: %d\n", finalval, pch, curval);
        pch = strtok(NULL, "\n");
    }
    printf("%d\n", finalval);
    free(sbuf);
    return 0;
}