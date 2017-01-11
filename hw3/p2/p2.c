#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int uniq(void *f, int n, int sz, int (*equals)(void *, void *), int (*h)(const void *key)) {
    Hashtable *ht = malloc(sizeof(Hashtable));
    ht -> binNum = 13131;
    ht -> hashFunc = h;
    ht -> equals = equals;
    intial(ht);
    int i = 0, done = 0, u = 0, back = n * sz - sz;
    /*for(int i =0; i < sz * n; i+= sz) {
        if(insert(ht, f + i)) u ++;
    }*/
    while(done < n){
        done ++;
        if(insert(ht, f + i)) {
            i += sz;
            u ++;
        }
        else {
            int j;
            for(j = back; j > i; j -= sz, back -= sz) {
                done ++;
                if(insert(ht, f + j)) {
                    memcpy(f + i, f + j, sz);
                    i += sz;
                    u++;
                    break;
                }
            }
        }
    }
    freeTable(ht);
    return u;
}

int intequal(void* a, void* b) {
    int *n1 = (int*) a;
    int *n2 = (int*) b;
    return *n1 == *n2;
}

int h(const void* key) {
    int* a = (int*) key;
    return *a; 
}


int doubleequal(void* a, void* b) {
    double *n1 = (double*) a;
    double *n2 = (double*) b;
    return *n1 == *n2;
}

int hh(const void* key) {
    double* a = (double*) key;
    return (int)(*a); 
}

int main() {
    
    double b[10000];
    int a[10000];
    for(int i = 0; i < 15; i++) {
        b[i] = rand()%33;
        a[i] = b[i];
    }
    printf("\n");
    int uu = uniq(b, 15, sizeof(double), doubleequal, hh);
    printf("%d\n", uu);
    for(int i = 0; i < uu; i++)
        printf("%.1lf ",b[i]);
    int u = uniq(a, 15, sizeof(int), intequal, h);
    printf("%d\n", u);
    for(int i = 0; i < u; i++)
        printf("%d ",a[i]);
}
