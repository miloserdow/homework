#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int x;
    struct Node* l;
    struct Node* r;
};

typedef struct Node Node;

inline void check_alloc(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Allocation failed\n");
        exit(1);
    }
}

Node* create_node(int x) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    check_alloc(tmp);
    tmp->x = x;
    tmp->l = NULL;
    tmp->r = NULL;
    return tmp;
}

void insert(Node* root, int x) {
    if (root->r == NULL) {
        root->r = create_node(x);
        return;
    }

    Node* cur = root->r;
    for (;;) {
        if (cur->x < x) {
            if (cur->r == NULL) {
                cur->r = create_node(x);
                return;
            }
            cur = cur->r;
        } else {
            if (cur->l == NULL) {
                cur->l = create_node(x);
                return;
            }
            cur = cur->l;
        }
    }

    return;
}

void erase(Node* root, int x) {
    Node* cur = root->r;
    Node* last = root;
    int dir = 1;
    for (;;) {
        if (x == cur->x) {
            if (cur->r == NULL) {
                cur->r = cur->l;
                cur->l = NULL;
            }
            if (dir == 1)
                last->r = cur->r;
            else
                last->l = cur->r;
            if (cur->r == NULL) {
                free(cur);
                return;
            }

            Node* tmp = cur->r;
            while (tmp->l != NULL)
                tmp = tmp->l;
            tmp->l = cur->l;
            free(cur);
            return;
        }
        last = cur;
        if (cur->x > x) {
            cur = cur->l;
            dir = 0;
        } else {
            cur = cur->r;
            dir = 1;
        }
    }
}

int check(Node* root, int x) {
    if (root->r == NULL)
        return 0;
    Node* cur = root->r;
    for (;;)
        if (cur == NULL)
            return 0;
        else if (cur->x == x)
            return 1;
        else if (cur->x > x)
            cur = cur->l;
        else 
            cur = cur->r;
}

void lower_print(Node* cur) {
    if (cur == NULL)
        return;
    lower_print(cur->l);
    printf("%d ", cur->x);
    lower_print(cur->r);
}

void upper_print(Node* cur) {
    if (cur == NULL)
        return;
    upper_print(cur->r);
    printf("%d ", cur->x);
    upper_print(cur->l);
}

void print(Node* root, int r) {
    if (root->r == NULL)
        return;
    Node* cur = root->r;
    if (r == 0)
        lower_print(cur);
    else if (r == 1)
        upper_print(cur);
    printf("\n");
}

void clean(Node* cur) {
    if (cur == NULL)
        return;
    clean(cur->l);
    clean(cur->r);
    free(cur);
}

int main() {
    Node* root = (Node*) malloc(sizeof(Node));
    check_alloc(root);
    root->l = root->r = NULL;
    root->x = 0;
    char c;
    int x;
    for (;;) {
        scanf(" %c", &c);
        switch (c) {
        case 'a':
            scanf("%d", &x);
            insert(root, x);
            printf("added %d\n", x);
            break;
        case 'r':
            scanf("%d", &x);
            erase(root, x);
            printf("erased %d\n", x);
            break;
        case 'c':
            scanf("%d", &x);
            if (check(root, x))
                printf("YES\n");
            else
                printf("NO\n");
            break;
        case 'p':
            scanf("%d", &x);
            print(root, x);
            break;
        case 'q':
            clean(root);
            printf("cleaning done\n");
            return 0;
        default:
            fprintf(stderr, "invalid command\n");
        }
    }
    return 0;
}
