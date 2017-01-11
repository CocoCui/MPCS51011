#ifndef __P1__
#define __P1__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 300000
#define MAX_INT 1000000000

typedef struct heapNode {
    int vertex, dis;
}HeapNode;

typedef struct edgenode {
  int y;
  int weight;
  struct edgenode *next;
} Edgenode;

typedef struct {
  Edgenode *edges[MAX_SIZE];
  int degree[MAX_SIZE];
  int nvertices;
  int nedges;
} Graph;

typedef struct heap{
    int heapsize;
    HeapNode* h;
    int* pos;
} Heap;

void swap(Heap *h, int id1, int id2);
void insert(Heap *h, int v, int d);
int getMin(Heap *h);
int max(int a, int b);
void init(Heap *h);



int dist1[MAX_SIZE], dist2[MAX_SIZE];


#endif
