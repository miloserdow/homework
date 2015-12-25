#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char n1[512], n2[512];

int main() {
    // n1[0] = n2[0] = \0 (for backward search to work)
    scanf("%s %s", n1 + 1, n2 + 1);
    char *p1 = n1 + 1, *p2 = n2 + 1;
    
    // move to the end
    while (*p1)
        p1++;
    --p1;
    while (*p2)
        p2++;
    --p2;

    // skip leading zeros
    while (*p1 == '0')
        *p1-- = 0;
    while (*p2 == '0')
        *p2-- = 0;
    
    // compare
    while (*p1 && *p2 && *p1 == *p2)
        --p1, --p2;
    if ((p1 - n1) > (p2 - n2)|| *p1 > *p2) {
        printf("first is greater\n");
    } else if (strlen(n2 + 1) > strlen(n1 + 1) || *p2 > *p1) {
        printf("second is greater\n");
    } else {
        printf("equal\n");
    }
    return 0;
}
