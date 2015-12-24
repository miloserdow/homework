#include <stdio.h>
#include <memory.h>

const int MAX_LEN = 255;

int main(void) {
    int array[MAX_LEN];
    memset(array, 0, MAX_LEN);
    int n;
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++) {
        char str[MAX_LEN];
        scanf("%s", &str);
        int j;
        for (j = 0; j < strlen(str); j++) {
            int x = (int)str[j];
            array[j] ^= x;
        }
    }
    for (i = 0; array[i] != 0; i++) {
        printf("%c", array[i]);
    }
    printf("\n");
}
