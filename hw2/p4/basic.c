#include "basic.h"

void freeNode(Node* n){
    free(n -> key);
    free(n -> val);
    free(n);
    return;
}

void lRotate(Node ** n) {
    Node* tmp = (*n) -> r;
    (*n) -> r = tmp -> l;
    tmp -> l = (*n);
    tmp -> size = (*n) -> size;
    (*n) -> size = (*n) -> l -> size  + (*n) -> r -> size + 1;
    (*n) = tmp;
    return;
}

void rRotate(Node ** n) {
    Node* tmp = (*n) -> l;
    (*n) -> l = tmp -> r;
    tmp -> r = (*n);
    tmp -> size = (*n) -> size;
    (*n) -> size = (*n) -> l -> size + (*n) -> r -> size + 1;
    (*n) = tmp;
    return;
}

void freeTree(Node * root){
    if(root == NULL || root == vNode) return;
    freeTree(root -> l);
    freeTree(root -> r);
    if(root -> val != NULL) free(root -> val);
    if(root -> key != NULL) free(root -> key);
    free(root);
    return;
}
