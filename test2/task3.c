#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 512

int main() {
    FILE* in = fopen("input.txt", "r");
    if (in == NULL) {
        fprintf(stderr, "ERROR: unable to open file\n");
        exit(1);
    }
    size_t nbytes = MAXLEN;
    char* cur = (char *) malloc (nbytes + 1);
    if (cur == NULL) {
        fprintf(stderr, "ERROR: malloc returned NULL\n");
        exit(1);
    }
    while (getline((char **) &cur, &nbytes, in) != -1) {
        char *p = cur;
        while (*p) {
            if (p[0] && p[1] && p[0] == '/' && p[1] == '/') {
                puts(p + 2);
                break;
            }
            p++;
        }
    }
    free(cur);
    fclose(in);
    return 0;
}

