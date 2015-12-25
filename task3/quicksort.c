#include <stdlib.h>
#include <stdio.h>

inline void swap(int *a, int *b) {
    int t=*a; 
    *a=*b; 
    *b=t;
}

void quicksort(int* arr, int b, int e) {
    if (e <= b + 1)
        return;
    int piv = arr[b], l = b + 1, r = e;
    while (l < r) {
        if (arr[l] <= piv)
            l++;
        else
            swap(&arr[l], &arr[--r]);
    }
    swap(&arr[--l], &arr[b]);
    quicksort(arr, b, l);
    quicksort(arr, r, e);
}

int main() {
    int n;
    scanf("%d", &n);
    int *a = (int *) malloc(n * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "ERROR: malloc returned NULL\n");
	exit(1);
    }
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    quicksort(a, 0, n);
    
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
