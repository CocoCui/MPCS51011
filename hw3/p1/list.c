#include "list.h"

int listInsert(Node* n, char* word, char* def) {
    while(n -> next != NULL) {
        if(strcmp(n -> next -> word, word) == 0) return 0;
        n = n -> next;
    }
    n -> next = createNode(word, def);
    return 1;
}

int listDelete(Node* n, char* word) {
    Node* pre = n;
    n = n -> next;
    while(n) {
        if(strcmp(n -> word, word) == 0) {
            pre -> next = n -> next;
            free(n -> word);
            free(n -> def);
            free(n);
            return 1;
        }
        pre = n;
        n = n -> next;
    }
    return 0;
}

Node* createNode(char* word, char* def) {
    Node* newNode = malloc(sizeof(Node));
    newNode -> word = malloc(sizeof(char) * strlen(word) + 1);
    newNode -> def = malloc(sizeof(char) * strlen(def) + 1);
    strcpy(newNode -> word, word);
    strcpy(newNode -> def, def);
    newNode -> next = NULL;
    return newNode;
}

Node* emptyNode() {
    Node* newNode = malloc(sizeof(Node));
    newNode -> word = NULL;
    newNode -> def = NULL;
    newNode -> next = NULL;
    return newNode;
}

