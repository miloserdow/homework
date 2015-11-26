#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

// This function tries to allocate memory and checks whether NULL is returned
void* alloc(size_t sz) {
    void* res = malloc(sz);
    if (res == NULL) {
        fprintf(stderr, "ERROR: malloc returned NULL\n");
	exit(1);
    }
    return res;
}

struct node {
    int value;
    node* next;
};

int main() {
    node* root = (node*) alloc(sizeof(node));
    root->next = NULL;
    char c;
    printf("Type the command (h for help)\n");
    for (;;) {
	do
	    c = getchar();
	while (isspace(c));
	int val;
        node* tmp;
        node* cur;
        switch (c) {
        case 'a':
            scanf("%d", &val);
            cur = root;
            while (cur->next != NULL)
                cur = cur->next;
            tmp = (node*) alloc(sizeof(node));
            tmp->value = val;
	    tmp->next = NULL;
            cur->next = tmp;
	    fprintf(stderr, "Done, %p was appended\n", tmp);
            break;
        case 'r':
            scanf("%d", &val);
            cur = root;
            tmp = root;
            while (cur->next != NULL) {
                tmp = cur;
                cur = cur->next;
                if (cur->value == val) {
                    fprintf(stderr, "Erasing %p...\n", cur);
		    fprintf(stderr, "Prev is %p, cur->next is %p\n", tmp, cur->next);
		    tmp->next = cur->next;
                    free(cur);
		    break;
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
	case 'b': // add cycle
	    cur = root;
	    while (cur->next != NULL)
	        cur = cur->next;
	    cur->next = root;
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
	case 'h':
	    printf("a x - Add x to the list\n");
	    printf("d x - Del first occurrence x from the list\n");
	    printf("p   - Print the list content\n");
	    printf("b   - Add cycle (break the list)\n");
	    printf("c   - Check whether the list is cyclic\n");
	    printf("q   - Quit\n");
	    break;
        default:
            printf("Invalid command. Use h for help\n");
            break;
        }
    }
    return 0;   
}
