#include <stdlib.h>
#include <stdio.h>

#define MAXVALUE 100000

int main() {
    int n;
    scanf("%d", &n);
    int* a = (int*) calloc(sizeof(int) * MAXVALUE, 0);
    if (a == NULL) {
        fprintf(stderr, "ERROR: malloc returned NULL\n");
        exit(1);
    }
    
    int i;
    for (i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        a[x] += 1;
    }
    
    for (i = 0; i <= n; i++)
        while (a[i]--)
            printf("%d ", i);
    putchar('\n');
    return 0;
}
