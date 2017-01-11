#include "basic.h"

Node* intial_m1() {
    Node* n = malloc(sizeof(Node));
    n -> l = NULL;
    n -> r = NULL;
    n -> key = NULL;
    return n;
}

void freeTree_m1(Node* r) {
    if(r -> l == NULL) return;
    if(r -> r == NULL) {
        free(r -> l);
        if(r -> key != NULL) free(r -> key);
        free(r);
    } else {
        freeTree_m1(r -> r);
        freeTree_m1(r -> l);
        if(r -> key != NULL) free(r -> key);
        free(r);
    }
    return;
}

char* find_m1(Node *n, char* key) {
    if(n -> l == NULL) {
        return NULL;
    }
    char* val;
    int res = strcmp(key, n -> key);
    if(n -> r == NULL) {
        if(res != 0) {   
            return NULL;
        } else {
            return (char*)(n -> l);
        }
    } else {
        if(res < 0) return find_m1(n -> l, key);
        else return find_m1(n -> r, key);
    }
}

void travelInOrder_m1(Node* n, int* idx) {
    if(n -> l == NULL) return;
    if(n -> r == NULL) {
        printf("Index: %d Key: %s Definition: %s\n", *idx, n -> key, (char*)n -> l);
        *idx = *idx + 1;
        return;
    }
    travelInOrder_m1(n -> l, idx);
    //printf("Key: %s\n", n -> key);
    travelInOrder_m1(n -> r, idx);
    return;
}

int insert_m1(char* key, char* val, Node **root) {
     if(key == NULL || val == NULL){
        return -1;
    }
    int res;
    Node* cur;
    if((*root) -> l == NULL) {
        (*root) -> l = malloc(sizeof(char) * strlen(val) + 1);
        (*root) -> key = malloc(sizeof(char) * strlen(key) + 1);
        strcpy((char*)((*root) -> l), val);
        strcpy((char*)((*root) -> key), key);
        (*root) -> r = NULL;
        return 1;
    } else {
        cur = * root;
        while(cur -> r != NULL) {
            res = strcmp(key, cur -> key);
            if(res < 0) cur = cur -> l;
            else cur = cur -> r;
        }
    }
    res = strcmp(key, cur -> key);
    if(res == 0) {
        return 0;
    }
    Node* old_leaf, *new_leaf;
    old_leaf = malloc(sizeof(Node));
    old_leaf -> l = cur -> l;
    old_leaf -> key = malloc(sizeof(char) * strlen(cur -> key) + 1);
    strcpy(old_leaf -> key, cur -> key);
    old_leaf -> r = cur -> r;
    new_leaf = malloc(sizeof(Node));
    new_leaf -> key = malloc(sizeof(char) * strlen(key) + 1);
    strcpy(new_leaf -> key, key);
    new_leaf -> l = malloc(sizeof(char) * strlen(val) + 1);
    strcpy((char*)(new_leaf -> l), val);
    new_leaf -> r = NULL;
    if(res > 0) {
        cur -> l = old_leaf;
        cur -> r = new_leaf;
        free(cur -> key);
        cur -> key = malloc(sizeof(char) * strlen(key) + 1);
        strcpy(cur -> key, key);
    } else {
        cur -> l = new_leaf;
        cur -> r = old_leaf;
    }
    return 1;
}

int deleteNode_m1(char* key, Node **rt) {
    Node *cur = *rt, *upper, *other;
    int res;
    if(cur -> l == NULL) return 0;
    else if (cur -> r== NULL) {
        res = strcmp(key, cur -> key);
        if(res == 0) {       
            char* res = (char*)(cur -> l);
            free(cur -> l);
            cur -> l = NULL;
            return 1;
        } else return 0;
    } else {
        cur = *rt;
        upper = NULL;
        while(cur -> r != NULL) {
            upper = cur;
            res = strcmp(key, cur -> key);
            if(res < 0) {
                cur = upper -> l;
                other = upper -> r;
            } else {
                cur = upper -> r;
                other = upper -> l;
            }
        }
        res = strcmp(key, cur -> key);
        if(res != 0) return 0;
        else {
            free(upper -> key);
            upper -> key = other -> key;
            upper -> l = other -> l;
            upper -> r = other -> r;
            free(cur -> l);
            free(cur -> key);
            free(cur);
            free(other);
            return 1;
        }
    }
}

int height_m1(Node *root) {
    if(root -> l == NULL) return 0;
    if(root -> r == NULL) return 1;
    int lh = height_m1(root -> l), rh = height_m1(root -> r);
    return lh > rh ? (lh + 1) : (rh + 1);
}
