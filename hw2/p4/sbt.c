#include "basic.h"

void maintain(Node **rt, int flag) {
    Node *t = *rt;
    if(flag) {
        if(t -> l -> size < t -> r -> l -> size) {
            rRotate(&(t -> r));
            lRotate(rt);
        } else if(t -> l -> size < t -> r -> r -> size){
            lRotate(rt);
        } else return;
    } else {
        if( t -> r -> size < t -> l -> r -> size) {
            lRotate(&(t -> l));
            rRotate(rt);
        } else if(t -> r -> size < t -> l -> l -> size) {
            rRotate(rt);
        } else return;
    }
    maintain(&((*rt) -> l), 0);
    maintain(&((*rt) -> r), 1);
    maintain(rt, 1);
    maintain(rt, 0);
    return;
}

Node* createNode(char* key, char *val) {
    Node *newNode = malloc(sizeof(Node));
    newNode -> key = malloc(sizeof(char) * strlen(key) + 1);
    newNode -> val = malloc(sizeof(char) * strlen(val) + 1);
    strcpy(newNode -> val, val);
    strcpy(newNode -> key, key);
    newNode -> l = vNode;
    newNode -> r = vNode;
    newNode -> size = 1;
    return newNode; 
}

int insert_sbt(char* key, char *val, Node** root) {
    if(key == NULL){
        return -1;
    }
    if((*root) == vNode) {
        *root = createNode(key, val);
        return 1;
    } else {
        int res = strcmp(key, (*root) -> key);
        (*root) -> size = (*root) -> size + 1;
        if(res < 0) {
            insert_sbt(key, val, &((*root) -> l));
            //maintain(root, 1);
            maintain(root, 0);
            return 1;
        } else if(res > 0) {
            insert_sbt(key, val, &((*root) -> r));
            //maintain(root, 0);
            maintain(root, 1);
            return 1;
        }
    }
    return 0;
}

void travelInOrder_sbt(Node* root, int* idx) {
    if(root == vNode) return;
    travelInOrder_sbt(root -> l, idx);
    printf("Index: %d Key: %s Definition: %s\n", *idx, root -> key, root -> val);
    *idx = *idx + 1;
    travelInOrder_sbt(root -> r, idx);
    return;
}

char* find_sbt(Node* cur, char* key) {
    //printf("find: %s\n", key);
    char *val = NULL;
    while(cur != vNode) {
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

int deleteNode_sbt(char* key, Node **rt) {
    Node *cur = *rt, *father = vNode;
    while(cur != vNode) {
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
    if(cur == vNode) {
        return 0; 
    }
    //maintrain size
    cur = *rt;
    while(cur != vNode) {
        cur -> size = cur -> size - 1;
        int res = strcmp(key, cur -> key);
        if(res > 0) cur = cur -> r;
        else if(res < 0) cur = cur -> l;
        else break;
    }
    if(cur -> l == vNode && cur -> r == vNode) {
        if(cur == *rt) *rt = vNode;
        else if(father -> r == cur) father -> r = vNode;
        else if(father -> l == cur) father -> l = vNode;
        freeNode(cur);
    } else if(cur -> l == vNode && cur -> r != vNode) {
        if(cur == *rt) *rt = cur -> r;
        else if(father -> r == cur) father -> r = cur -> r;
        else if(father -> l == cur) father -> l = cur -> r;
        freeNode(cur);
    } else if(cur -> l != vNode && cur -> r == vNode) {
        if(cur == *rt) *rt = cur -> l;
        else if(father -> r == cur) father -> r = cur -> l;
        else if(father -> l == cur) father -> l = cur -> l;
        freeNode(cur);
    } else  {
        Node *pre = cur -> l, *fpre = cur;
        while(pre -> r != vNode) {
            fpre -> size = fpre -> size - 1;;
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

Node* intial_sbt() {
    vNode = malloc(sizeof(Node));
    vNode -> r = vNode;
    vNode -> l = vNode;
    vNode -> size = 0;
    return vNode;
}

int height_sbt(Node *root) {
    if(root == vNode) return 0;
    int lh = height_sbt(root -> l), rh = height_sbt(root -> r);
    return lh > rh ? (lh + 1) : (rh  + 1);
}




