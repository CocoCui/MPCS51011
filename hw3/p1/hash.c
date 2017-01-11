#include "hash.h"


void intial(Hashtable *t, int binNum, char* hashFuncName, int(* hashFunc)(void* hashkey)) {
    t -> hashFunc = hashFunc;
    t -> binNum = binNum;
    t -> table = malloc(sizeof(Node*) * (t -> binNum));
    t -> binsize = malloc(sizeof(int) * (t -> binNum));
    t -> hashFuncName = hashFuncName;
    for(int i = 0; i < t -> binNum; i++) {
        (t -> table)[i] = emptyNode();
        (t -> binsize)[i] = 0;
    }
    return;
}

int insert(Hashtable *t, void* key, void* data, int log) {
    int id = t -> hashFunc(key) % (t -> binNum);
    int res = listInsert((t -> table)[id], key, data);
    if(res) (t -> binsize)[id] += 1;
    if(log) createLog(t, "Insert", key);
    return res;
}

int delete(Hashtable *t, void* key) {
    int id = t -> hashFunc(key) % (t -> binNum);
    int res = listDelete((t -> table)[id], key);
    if(res) (t -> binsize)[id] -= 1;
    createLog(t, "Detete", key);
    return res;
}

void createLog(Hashtable *t, char* operation, char* key) {
    double keys = 0;
    int minsize  = 2147483647;
    int maxsize = 0;
    for(int i = 0; i < t -> binNum; i++) {
        keys += t -> binsize[i];
        if(t -> binsize[i] > maxsize) maxsize = t -> binsize[i];
        if(t -> binsize[i] < minsize) minsize = t -> binsize[i];
    }
    fprintf(t -> logfile, "HashFunc: %s    Op: %s    Key: %s    ", t -> hashFuncName, operation, key);
    fprintf(t -> logfile, "LF: %f     OCC([min, max] depth): [%d, %d]\n", keys / t -> binNum, minsize, maxsize);
    fflush(t -> logfile);
    return;
}

int BKDRHash(void* key) {
    unsigned int seed = 131;
    unsigned hash = 0;
    char* str = (char*) key;
    while(*str) {
        hash = hash * seed + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

int SUMHash(void* key) {
    unsigned hash = 0;
    char* str = (char*) key;
    while(*str) {
        hash += *str;
        str++;
    }
    return (hash & 0x7FFFFFFF);
}

int DJBHash(void *key){
    unsigned int hash = 5381;
    char* str = (char*) key;
    while (*str){
        hash += (hash << 5) + (*str++);
    }
    return (hash & 0x7FFFFFFF);
}

int part(Node *words[], int l, int r) {
    int i = l, j;
    Node* p = words[r], *temp  = NULL;
    for(j = l; j < r; j++) {
        if(strcmp(words[j] -> word, p -> word) < 0) {
            temp = words[j];
            words[j] = words[i];
            words[i] = temp;
            i ++;
        }
    }
    temp = words[r];
    words[r] = words[i];
    words[i] = temp;
    return i;
}

void quickSort(Node *words[], int l, int r) {
    if(l < r) {
        int p = part(words, l, r);
        quickSort(words, l, p - 1);
        quickSort(words, p + 1, r);
    }
    return;
}

void travel(Hashtable *t) {
    Node* nodes[1000000];
    int id = 0;
    for(int i = 0; i < t -> binNum; i++) {
        Node* cur = (t -> table)[i];
        while(cur) {
            if(cur -> word != NULL) nodes[id++] = cur;
            cur = cur -> next;
        }
    }
    quickSort(nodes, 0, id-1);
    for(int i = 0; i < id; i ++) {
        printf("Word: %s Definition: %s\n", nodes[i] -> word, nodes[i] -> def);
    }
    return;
}

void reHash(Hashtable *t, int binNum, char* hashFuncName, int(* hashFunc)(void* hashkey)) {
    Node* nodes[1000000];
    int id = 0;
    for(int i = 0; i < t -> binNum; i++) {
        Node* cur = (t -> table)[i];
        while(cur) {
            if(cur -> word != NULL) nodes[id++] = cur;
            cur = cur -> next;
        }
    }
    intial(t, binNum, hashFuncName, hashFunc);
    for(int i = 0; i < id; i++) {
        insert(t, nodes[i] -> word, nodes[i] -> def, 0);
        free(nodes[i] -> word);
        free(nodes[i] -> def);
        free(nodes[i]);
    }
    createLog(t, "ReHash", "");
    return;
}

void findWords(Hashtable *t, char* word1, char *word2) {
    Node* nodes[100000];
    int id = 0;
    for(int i = 0; i < t -> binNum; i++) {
        Node* cur = (t -> table)[i];
        while(cur) {
            if(cur -> word != NULL) nodes[id++] = cur;
            cur = cur -> next;
        }
    }
    quickSort(nodes, 0, id-1);
    if(strcmp(word1, word2) > 0) {
        char* temp;
        temp = word1;
        word1 = word2;
        word2 = word1;
    }
    for(int i = 0; i < id; i++) {
        if(strcmp(word1, nodes[i] -> word) <= 0 && strcmp(nodes[i] -> word ,word2) <= 0) {
            printf("Word: %s Definition: %s\n", nodes[i] -> word, nodes[i] -> def);
        }
    }
    return;
}

