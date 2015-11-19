#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *) malloc(n * sizeof(int));
    int i, j;
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    int t;
    for (i = n - 1; i >= 0; i--) {
        for (j = 0; j < i; j++) {
            if (a[j] > a[j + 1]) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
    
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
