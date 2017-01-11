#include <stdlib.h>
#include <stdio.h>

typedef struct pair_{
  int x;
  int y;
} Pair;
Pair p[] = { {-5,3}, {-1,-2}, {0,0}, { 1,3}, {2,-1}, {3,-2}, {5,-1}, {10,0}, {100,-1}};

int cmp(const void *a, const void *b) {
    Pair *pa = (Pair*) a;
    Pair *pb = (Pair*) b;
    if(pa -> x > pb -> x) return 1;
    else if(pa -> x < pb -> x) return -1;
    else return pa -> y - pb -> y;
}

int main() {
    Pair t = {10,0};
    void *ptr = bsearch((void*)&t, p, sizeof(p) / sizeof(p[0]), sizeof(p[0]), cmp);
    Pair* pt = (Pair*)ptr;
    printf("address of {%d,%d} is %p\n", pt -> x, pt -> y, ptr);
    return 0;
}
