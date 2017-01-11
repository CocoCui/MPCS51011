#ifndef _LIST_
#define _LIST_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    struct node* next;
    void* data;
}Node;

int listInsert(Node* n, void* data, int(* equals)(void* a, void*b));
Node* createNode(void* data);
Node* emptyNode();
void freeNode(Node* n);

#endif
