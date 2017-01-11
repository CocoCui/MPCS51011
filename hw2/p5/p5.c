#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Tree_node{
      struct Tree_node *left, *right;
      int data;
} Tree_node;


struct node {
    struct node* prev;
    void* ptr;
};

struct stack{
    struct node* top;
    int size;
};

void push(void* t, struct stack *s) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->prev = s->top;
    newNode->ptr = t;
    s->top = newNode;
    s->size ++;
    return;
}

void* pop(struct stack *s) {
    if(s->size == 0) return NULL;
    void* ret = s->top;
    s->top = s->top->prev;
    s->size --;
    return ret;
}

/* none recursive version 
 * using a stack to store the precursor of a node
 */
int isValidBST(Tree_node* root) {
    if(!root) return 1;
    struct stack *s = malloc(sizeof(struct stack));
    struct node* n;
    long last = LONG_MIN;
    s->size = 0;
    while(root || s -> size > 0) {
        while(root) {
            push(root, s);
            root = root -> left;
        }
        n = pop(s);
        root = (Tree_node*)(n->ptr);
        free(n);
        if(root-> data > last) last = root->data;
        else return 0;
        root = root -> right;
    }
    return 1;
}

/* recursive version 
 * call valid(root, LONG_MIN, LONG_MAX) to check is the tree is valid
 */
int valid(Tree_node* r, long lower, long upper) {
    if(r == NULL) return 1;
    return (r -> data > lower && r -> data < upper && valid(r->left, lower, r->data) && valid(r->right, r->data, upper));
}

int main() {

}


