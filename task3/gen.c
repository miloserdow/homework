#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), i;
    printf("%d\n", n);
    for (i = 0; i < n; i++)
        printf("%d ", rand());
    printf("\n");
    return 0;
}
