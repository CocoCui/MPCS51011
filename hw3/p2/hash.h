#ifndef _HASH_
#define _HASH_
#include "list.h"

typedef struct hashtable{
    Node ** table;
    int binNum;
    int(* hashFunc)(const void* hashkey);
    int(* equals)(void* a, void*b);
}Hashtable;


void intial(Hashtable *t);
int insert(Hashtable *t, void* data);
void freeTable(Hashtable *t);
#endif
