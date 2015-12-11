#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char str[512], c;

int main() {
    scanf("%s %c", str, &c);
    char *p1 = str, *p2 = str;
    while (*p1) {
        *p2 = *p1++;
        p2 += (*p2 != c);
    }
    *p2 = '\0';
    puts(str);
    return 0;
}
