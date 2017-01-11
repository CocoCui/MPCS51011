#ifndef _BASIC_
#define _BASIC_

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    struct node *l, *r;
    int size;
    char* key;
    char* val;
}Node;

Node *vNode;
void freeNode(Node* n);
void lRotate(Node ** n);
void rRotate(Node ** n);
void freeTree(Node * root);
#endif
