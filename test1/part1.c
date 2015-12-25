#include <stdio.h>

size_t str_len(char * str) {
    char * start = str;
    while(*str++);
    return str - start - 1;
}

int str_cmp(char * s1, char * s2) {
    int i;
    for (i = 0; *s1 != '\0' && *s2 != '\0'; i++) {
        char ch = *s1++ - *s2++;
        if (ch != 0) {
            return ch;
        }
    }
    if (*s1 == '\0' && *s2 == '\0') {
        return 0;
    } else if (*s1 == '\0') {
        return -1;
    } else if (*s2 == '\0') {
        return 1;
    }
    return 0;
}

void str_cpy(char * dst, char * src) {
    do {
        *dst++ = *src;
    } while (*src++);
}

void str_cat(char * dst, char * src) {
    while(*dst) dst++;
    do {
        *dst++ = *src;
    } while (*src++);
}

int main() {
    char str1[] = "123", str2[] = "456";
    return 0;
}
