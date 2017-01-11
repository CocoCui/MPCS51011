#include "hash.h"

void intial(Hashtable *t) {
    t -> table = malloc(sizeof(Node*) * (t -> binNum));
    for(int i = 0; i < t -> binNum; i++) (t -> table)[i] = emptyNode();
    return;
}
int insert(Hashtable *t, void* data) {
    int id = t -> hashFunc(data) % (t -> binNum);
    return listInsert((t -> table)[id], data,  t -> equals);
}

void freeTable(Hashtable *t) {
    for(int i = 0; i < t -> binNum; i++) freeNode((t -> table)[i]);
    free(t -> table);
    free(t);
}
