#include <stdio.h>

int main(void) {
    hash_table table;
    char str[80];
    int count;
    scanf("%d", count);
    int i;
    for (i = 0; i < count; i++) {
        scanf("%s", str);
        insert(table, str);
    }
    print_count_word(table); // function that prints word counts stats
    printf("%d\n", ans);
    return 0;
}
