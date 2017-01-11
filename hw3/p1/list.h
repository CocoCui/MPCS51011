#ifndef _LIST_
#define _LIST_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
    struct node* next;
    char* word;
    char* def;
}Node;

int listInsert(Node* n, char* word, char* def);
int listDelete(Node* n, char* word);
Node* createNode(char *word, char *def);
Node* emptyNode();

#endif
