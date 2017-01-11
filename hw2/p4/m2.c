#include "basic.h"

Node* intial_m2() {
    return NULL;
}

int insert_m2(char* key, char *val, Node** root) {
    if(key == NULL){
        return -1;
    }
    Node *newNode = malloc(sizeof(Node));
    Node *cur = *root;
    newNode -> key = malloc(sizeof(char) * strlen(key) + 1);
    newNode -> val = malloc(sizeof(char) * strlen(val) + 1);
    strcpy(newNode -> val, val);
    strcpy(newNode -> key, key);
    newNode -> l = NULL;
    newNode -> r = NULL;
    if(*root == NULL) {
        *root = newNode;
        return 1;
    }
    int res = strcmp(key, cur -> key);
    while(res != 0) {
        if(res > 0) {
            if(cur -> r == NULL) {
                cur -> r = newNode;
                return 1;
            } else cur = cur -> r;
        }
        else if(res < 0){
            if(cur -> l == NULL) {
                cur -> l = newNode;
                return 1;
            } else cur = cur -> l;
        }
        res = strcmp(key, cur -> key);
    }
    return 0;
}

void travelInOrder_m2(Node* root, int* idx) {
    if(!root) return;
    travelInOrder_m2(root -> l, idx);
    printf("Index: %d Key: %s Definition: %s\n", *idx, root -> key, root -> val);
    *idx = *idx + 1;
    travelInOrder_m2(root -> r, idx);
    return;
}

char* find_m2(Node* cur, char* key) {
    //printf("find: %s\n", key);
    char *val = NULL;
    while(cur != NULL) {
        int res = strcmp(key, cur -> key);
        if(res > 0) cur = cur -> r;
        else if(res < 0) cur = cur -> l;
        else {
            val = cur -> val;
            return val;
        }
    }
    return val;
}

int deleteNode_m2(char* key, Node **rt) {
    Node *cur = *rt, *father = NULL;
    while(cur != NULL) {
        int res = strcmp(key, cur -> key);
        if(res > 0) {
            father = cur;
            cur = cur -> r;
        }
        else if(res < 0) {
            father = cur;
            cur = cur -> l;
        }
        else break;
    }
    if(cur == NULL) {
        return 0; 
    }
    if(cur -> l == NULL && cur -> r == NULL) {
        if(cur == *rt) *rt = NULL;
        else if(father -> r == cur) father -> r = NULL;
        else if(father -> l == cur) father -> l = NULL;
        freeNode(cur);
    } else if(cur -> l == NULL && cur -> r != NULL) {
        if(cur == *rt) *rt = cur -> r;
        else if(father -> r == cur) father -> r = cur -> r;
        else if(father -> l == cur) father -> l = cur -> r;
        freeNode(cur);
    } else if(cur -> l != NULL && cur -> r == NULL) {
        if(cur == *rt) *rt = cur -> l;
        else if(father -> r == cur) father -> r = cur -> l;
        else if(father -> l == cur) father -> l = cur -> l;
        freeNode(cur);
    } else  {
        Node *pre = cur -> l, *fpre = cur;
        while(pre -> r) {
            fpre = pre;
            pre = pre -> r;
        }
        free(cur -> val);
        free(cur -> key);
        cur -> key = pre -> key;
        cur -> val = pre -> val;
        if(fpre == cur) {
            cur -> l = pre -> l;
        } else {
            fpre -> r = pre -> l;
        }
        free(pre);
    }
    return 1;
}

int height_m2(Node *root) {
    if(root == NULL) return 0;
    int lh = height_m2(root -> l), rh = height_m2(root -> r);
    return lh > rh ? (lh + 1) : (rh  + 1);
}

