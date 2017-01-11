#ifndef _HASH_
#define _HASH_
#include "list.h"
#include <string.h>

typedef struct hashtable{
    Node ** table;
    int* binsize;
    int binNum;
    int(* hashFunc)(void* hashkey);
    FILE* logfile;
    char* hashFuncName;
}Hashtable;

void intial(Hashtable *t, int binNum, char* hashFuncName, int(* hashFunc)(void* hashkey));
void reHash(Hashtable *t, int binNum, char* hashFuncName, int(* hashFunc)(void* hashkey));
int insert(Hashtable *t, void* key, void* data, int log);
int delete(Hashtable *t, void* key);
int BKDRHash(void* key);
int SUMHash(void* key);
int DJBHash(void* key);
void travel(Hashtable *t);
void quickSort(Node *words[], int l, int r);
int part(Node *words[], int l, int r);
void createLog(Hashtable *t, char* operation, char* key);
void findWords(Hashtable *t, char* word1, char *word2);

#endif
