#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p5.h"
#define MAX_CHAR_PER_LINE 10000

int max(int a, int b) {
    return a > b ? a : b;
}

int read_file(Graph *g, char* name) {
    FILE* f = fopen(name, "r");
    int linenum = 0, v, u;
    double p;
    size_t r, len = MAX_CHAR_PER_LINE;
    char *line = NULL, *start;
    while((r = getline(&line, &len, f)) != -1) {
        sscanf(line, "%d", &u);
        g -> nvertices = max(g -> nvertices, u);
        start = line;
        while(1) {
            while(*start != '[' && *start != '\0') start ++;
            if(*start == '\0') break;
            if(sscanf(start, "[%d, %lf]", &v, &p) == 2) {
                start ++;
                Edgenode *new_node = (Edgenode *) malloc(sizeof(Edgenode));          
                Edgenode *prev = g -> edges[u];
                if (g -> edges[u] == NULL){
                    g -> edges[u]          = new_node;
                    g -> edges[u]->y       = v;
                    g -> edges[u]-> weight = p;
                    g -> edges[u]->next    = NULL;
                }
                else{
                    while(prev -> next != NULL) prev = prev -> next;
                    prev->next          = new_node;
                    new_node->y         = v;
                    new_node->weight    = p;
                    new_node->next      = NULL;
                    prev                = new_node;
                }
            }    
            else break;
        }
    }
    fclose(f);
    return linenum;
}

int visited[MAX_SIZE];
int node[MAX_SIZE];

int instack[MAX_SIZE];
int stack[MAX_SIZE];  
int belong[MAX_SIZE];
int DFN[MAX_SIZE];
int LOW[MAX_SIZE]; 
int idx; 
int top = 0;  
int scc = 0; 

void strongConnect(Graph *g, int u) {
    int i, j, v;
    //set depth index for u
    idx ++;
    LOW[u] = idx;
    DFN[u] = idx;
    
    //push u into the stac;
    instack[u] = 1;
    stack[top] = u;
    top ++;
    
    //Consider successors of v
    Edgenode *iter = g -> edges[u];
    while(iter != NULL) {
        v = iter -> y;
        
        if(DFN[v] == 0) {
            //recurese on the successor that has not been visited
            strongConnect(g, v);
            if(LOW[v] < LOW[u]) LOW[u] = LOW[v];
        } else {
            //successor v is in stack and hence in the curren SCC
            if(instack[v] && DFN[v] < LOW[u]) LOW[u] = DFN[v];
        }
        iter = iter -> next;
    }
    
    // create an SCC 
    if(DFN[u] == LOW[u]) {
        scc ++;
        do {
            j = stack[--top];
            instack[j] = 0;
            belong[j] = scc;
        }
        while(j != u);
    }
    return;
}

void tarjan(Graph *g) {
    for(int i = 1; i <= g -> nvertices; i++) {
        if(DFN[i] == 0) strongConnect(g, i);
    }
    return;
}

int main(int argc, char** argv) {
    int i;
    int period[MAX_SIZE];
    Graph g;
    g.nvertices = 0;
    g.nedges = 0;
    for (i = 0; i < MAX_SIZE; i++) g.edges[i] = NULL;
    read_file(&g, argv[1]);
    tarjan(&g);
    if(scc == 1) {
        printf("The input Markov Graph is irreducible.\n");
    }
    else {
        printf("The input Markov Graph is not irreducible, since there're %d strongly connected components in the graph.\n", scc);
    }
    return 0;
}

