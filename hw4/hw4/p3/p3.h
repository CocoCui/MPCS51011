#ifndef __P1__
#define __P1__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 300000
#define MAX_INT 1000000000
#
typedef struct heapNode {
    int vertex, dis;
}HeapNode;

typedef struct edgenode {
  int y;
  int weight;
} Edgenode;

typedef struct {
  Edgenode *edges[MAX_SIZE];
  int degree[MAX_SIZE];
  int nvertices;
  int nedges;
} Graph;

int heapsize  = 0;
HeapNode h[3000000];
int pos[3000000];


void swap(int id1, int id2);
void insert(int v, int d);
int getMin();
int max(int a, int b);
void dijkstra(Graph *g, int start, int *distance, int nt);
void dijkstra_optimal(Graph *g, int start, int *distance);

#endif
