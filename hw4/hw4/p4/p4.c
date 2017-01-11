#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p4.h"
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

int length[100000000];
int tot_len = 0;;
int visited[MAX_SIZE];

void dfs(int begin, int cur, int depth, Graph *g) {
    Edgenode *n = g -> edges[cur];
    visited[cur] = 1;
    while(n -> next != NULL){
        int nxt = n -> y;
        n = n -> next;
        if(nxt == begin) {
            length[tot_len++] = depth+1;
        }
        if(visited[nxt]) continue;
        dfs(begin, nxt, depth + 1, g);
    }
    return;
}

int gcd(int x, int y)  
{     
    int z = y;  
    while(x%y!=0)  
    {  
        z = x%y;  
        x = y;  
        y = z;    
    }  
    return z;  
}

int gcd_seq() {
    int cur = gcd(length[0], length[1]);
    for(int i = 2; i < tot_len; i++) {
        cur = gcd(cur, length[i]);
        if(cur == 1) return 1;
    }
    return cur;
}
int main(int argc, char** argv) {
    int period[MAX_SIZE];
    Graph g;
    g.nvertices = 0;
    g.nedges = 0;
    for(int i = 0; i < MAX_SIZE; i++) g.edges[i] = NULL;
    read_file(&g, argv[1]);
    dfs(98, 98, 0, &g);
    for(int i = 1; i <= g.nvertices; i++) {
        memset(visited, 0, sizeof(visited));
        dfs(i, i, 0, &g);
    }
    printf("period: %d\n", gcd_seq());
    return 0;
}

