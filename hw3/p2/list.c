#include "list.h"

int listInsert(Node* n, void* data, int(* equals)(void* a, void*b)) {
    while(n -> next) {
        if(equals(data, n -> next -> data)) return 0;
        n = n -> next;
    }
    n -> next = createNode(data);
    return 1;
}

Node* createNode(void* data) {
    Node* newNode = malloc(sizeof(Node));
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}

Node* emptyNode() {
    Node* newNode = malloc(sizeof(Node));
    newNode -> data = NULL;
    newNode -> next = NULL;
    return newNode;
}

void freeNode(Node* n) {
    if(n -> next == NULL) {
        free(n);
        return;
    }
    freeNode(n -> next);
    free(n);
}



