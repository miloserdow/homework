#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* r;
    struct Node* l;
};

typedef struct Node Node;

Node* init(int x) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        fprintf(stderr, "ERROR: malloc returned NULL\n");
        exit(1);
    }
    tmp->val = x;
    tmp->l = NULL;
    tmp->r = NULL;
    return tmp;
}

Node* insert(Node* root, int x) {
    if (root == NULL) 
        return init(x);
    else if (root->val < x)
        root->r = insert(root->r, x);
    else if (root->val > x)
        root->l = insert(root->l, x);
    return root;
}

Node* min(Node* root) {
    if (root == NULL)
        return NULL;
    while (root->l)
        root = root->l;
    return root;
}

int find(Node* root, int x) {
    if (root->val == x) 
        return 1;
    if (root->val > x) {
        if (root->l)
            find(root->l, x);
        else
            return 0;
    } else if (root->val < x) {
        if (root->r)
            find(root->r, x);
        else
            return 0;
    }
    return 0;
}

Node* erase(Node* root, int x) {
    if (root == NULL)
        return NULL;
    if (root->val < x)
        root->r = erase(root->r, x);
    else if (root->val > x)
        root->l = erase(root->l, x);
    else {
        if ((root->r) && (root->l)) {
            Node* right_min = min(root->r);
            root->val = right_min->val;
            root->r = erase(root->r,right_min->val);
            return root;
        } else if (root->r) {
            Node* cur = root->r;
            free(root);
            return cur;
        } else if (root->l) {
            Node* cur = root->l;
            free(root);
            return cur;
        } else {
            free(root);
            return NULL;
        }
    }
    return root;
}

void print(Node* root) {
    if (root == NULL)
        return;
    
    printf("(%d ",root->val);
    if (root->l)
        print(root->l);
    else
        puts("null");
    puts(" ");
    if (root->r) {
        print(root->r);
        puts(")");
    } 
    else
        puts(" null)");
}

void print_min(Node* root) {
    if (root == NULL)
        return;
    print_min(root->l);
    printf("%d\n", root->val);
    print_min(root->r);
}

void print_max(Node* root) {
    if (root == NULL)
        return;
    print_max(root->r);
    printf("%d ", root->val);
    print_max(root->l);
}

void clean_tree(Node* root) {
    if (root == NULL)
        return;
    clean_tree(root->l);
    clean_tree(root->r);
    free(root);
}

int main() {
    char c;
    Node* root = NULL;
    printf("Type the command (h for help)\n");
    for (;;) {
        do
            c = getchar();
        while (isspace(c));
        int val;
        switch (c) {
        case 'a':
            scanf("%d", &val);
            root = insert(root, val);
            break;
        case 'r':
            scanf("%d", &val);
            root = erase(root, val);
            break;
        case 'p':
            print(root);
            break;
        case 'x':
            print_max(root);
            break;
        case 'm':
            print_min(root);
            break;
        case 'q':
            clean_tree(root);
            return 0;
        case 'h':
            printf("a x - Add x to the tree\n");
            printf("r x - Erase x\n");
            printf("p   - Print the tree\n");
            printf("x   - Print from min to max\n");
            printf("m   - Print from max to min\n");
            printf("q   - Quit\n");
            break;
        default:
            printf("Invalid command. Use h for help\n");
            break;
        }
    }
    return 0;
}
