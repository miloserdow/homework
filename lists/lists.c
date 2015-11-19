#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
    int value;
    node* next;
};

int main() {
    node* root = (node*) malloc(sizeof(node)); 
    root->next = NULL;
    char c;
    for (;;) {
        scanf("  %c", &c);
        int val;
        node* tmp;
        node* cur;
        switch (c) {
        case 'a':
            scanf("%d", &val);
            cur = root;
            while (cur->next != NULL)
                cur = cur->next;
            tmp = (node*) malloc(sizeof(node));
            tmp->value = val;
            cur->next = tmp;
            break;
        case 'd':
            scanf("%d", &val);
            cur = root;
            tmp = NULL;
            while (cur->next != NULL) {
                tmp = cur;
                cur = cur->next;
                if (cur->value == val) {
                    tmp->next = cur->next;
                    free(cur);
                    cur = tmp;
                }
            }
            break;
        case 'p':
            cur = root;
            while (cur->next != NULL) {
                cur = cur->next;
                printf("%d ", cur->value);
            }
            printf("\n");
            break;
        case 'q':
            cur = root;
            while (cur->next != NULL) {
                tmp = cur;
                free(tmp);
                cur = cur->next;
            }
            exit(0);
            break;
        case 'c': // check for cycles
            cur = tmp = root;
            char torch = 0, wasCycle = 0;
            for (;;) {
                if (torch) {
                    if (cur->next != NULL)
                        cur = cur->next;
                    else
                        break;
                } else {
                    if (tmp->next != NULL && tmp->next->next != NULL)
                        tmp = tmp->next->next;
                    else
                        break;
                }
                if (tmp == cur) {
                    wasCycle = 1;
                    break;
                }
                torch = !torch;
            }
            printf("%s\n", wasCycle ? "Cyclic" : "Non-Cyclic");
            break;
        default:
            printf("Invalid command\n");
            break;
        }
    }
    return 0;   
}
