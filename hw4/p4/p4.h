#ifndef __P4__
#define __P4__
#define MAX_SIZE 20000
typedef struct edgenode {
  int y;
  double weight;
  struct edgenode *next;
} Edgenode;

typedef struct {
  Edgenode *edges[MAX_SIZE];
  int degree[MAX_SIZE];
  int nvertices;
  int nedges;
} Graph;

#endif
