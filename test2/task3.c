#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 512

int main() {
    FILE* in = fopen("input.txt", "r");
    size_t nbytes = MAXLEN;
    char* cur = (char *) malloc (nbytes + 1);
    while (getline((char **) &cur, &nbytes, in) != -1) {
        if (cur[0] && cur[1] && cur[0] == '/' && cur[1] == '/')
            puts(cur + 2);
    }
    free(cur);
    fclose(in);
    return 0;
}
