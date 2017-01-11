#ifndef _DIC_
#define _DIC_

#include "basic.h"

typedef struct dic {
    Node* (*intial)();
    char* (*find)(Node *n,char *key);
    void (*travel)(Node* n, int* idx);
    int (*insert)(char* key, char* val, Node **rt);
    int (*delete)(char* key, Node **rt);
    int (*height)(Node *rt);
    char* treeType;
    Node* root;
    void (*freeTree)(Node *root);
}Dictionary;

char* genString(int len);
void insert(char *key, char* val, Dictionary *d);
void travel(Dictionary* d);
char* find(char* key, Dictionary *d); 
void cmd(Dictionary *d);
void delete(char* key, Dictionary *d);
void height(Dictionary *d);
#endif

