#include "p2.h"
#include <omp.h>



void swap(Heap* h,int id1, int id2) {
    int temp;
    temp = h -> pos[h ->h[id1].vertex];
    h -> pos[h ->h[id1].vertex] = h -> pos[h ->h[id2].vertex];
    h -> pos[h ->h[id2].vertex] = temp;
    temp = h -> h[id1].vertex;
    h -> h[id1].vertex = h -> h[id2].vertex;
    h -> h[id2].vertex = temp;
    temp = h -> h[id1].dis;
    h -> h[id1].dis = h -> h[id2].dis;
    h -> h[id2].dis = temp;
    return;
}

void insert(Heap* h,int v, int d) {
    h -> heapsize += 1;
    h -> h[h -> heapsize].vertex = v;
    h -> h[h -> heapsize].dis = d;
    h -> pos[v] = h -> heapsize;
    int cur = h -> heapsize;
    while(cur > 1 && h -> h[cur].dis < h -> h[cur/2].dis) {
        swap(h, cur, cur/2);
        cur /= 2;
    }
    return;
}

int getMin(Heap* h) {
    int min = h -> h[1].vertex;
    swap(h, h -> heapsize, 1);
    h -> heapsize --;
    if(h -> heapsize > 0) {
        int cur = 1;
        while(cur * 2 <= h -> heapsize) {
            cur *= 2;
            if(cur < h -> heapsize && h -> h[cur].dis > h -> h[cur + 1].dis) cur ++;
            if(h -> h[cur].dis < h -> h[cur/2].dis) swap(h, cur, cur/2);
            else break;
        }
    }
    return min;
}

void decrease(Heap* h, int idx, int newdis) {
    h -> h[idx].dis = newdis;
    while(idx > 1 && h -> h[idx].dis < h -> h[idx/2].dis) {
        swap(h, idx, idx/2);
        idx /= 2;
    }
    return;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void init(Heap* h) {
    h -> h = malloc(sizeof(HeapNode) * MAX_SIZE);
    h -> pos = malloc(sizeof(int) * MAX_SIZE);
    return;
}

void freeHeap(Heap* h) {
    free(h -> h);
    free(h -> pos);
    return;
}
void dijkstra(int *processed, Graph *g, int start, int *distance){
    int v, w, weight, dist, count = 0;
    Edgenode *p;
    for(int i = 0; i < g -> nvertices; i++) {
        processed[i] = 0;
        distance[i] = MAX_INT;
    }
    distance[start] = 0;
    v = start;
  
    /* add v to processed list and update distance of neighbors */
    while (count < g -> nvertices && processed[v] == 0) {
        processed[v] = 1;
        p = g->edges[v];
        while (p != NULL) {
            w = p -> y;
            weight = p->weight;
            p = p -> next;
            if(processed[w]) continue;
            if(distance[w] > (distance[v] + weight)) distance[w] = distance[v] + weight;
        }
        dist = MAX_INT;
        for (int i = 0; i < g -> nvertices; i++)
            if ((processed[i] == 0) && (dist > distance[i])) {
	            dist = distance[i];
	            v = i;
            }
        count ++;
    }
    return;
}

void dijkstra_optimal(int *processed, Graph *g, int start, int *distance){
    int v, w, weight, dist, count = 0;
    Edgenode *p;
    Heap h;
    init(&h);
    h.heapsize = 0;
    for(int i = 0; i < g -> nvertices; i++) {
        processed[i] = 0;
        distance[i] = MAX_INT;
    }
    distance[start] = 0;
    for(int i = 0; i < g -> nvertices; i++) insert(&h, i, distance[i]);
    v = getMin(&h);
    /* add v to processed list and update distance of neighbors */
    while (count < g -> nvertices && processed[v] == 0) {
        processed[v] = 1;
        p = g->edges[v];
        while (p != NULL) {
            w = p -> y;
            weight = p->weight;
            p = p -> next;
            if(processed[w]) continue;
            if(distance[w] > (distance[v] + weight)) {
                distance[w] = distance[v] + weight;
                decrease(&h, h.pos[w], distance[w]);
            }
        }
        v = getMin(&h);
        count ++;
    }
    return;
}

int main(int argc, char **argv) {
    Graph g;
    Edgenode *e;
    FILE *file;
    char *filename;
    int u,v,w;
    int i;
    g.nvertices = 0;
    g.nedges = 0;
    for (i = 0; i < MAX_SIZE;++i)
        g.edges[i] = NULL;
  
    filename = argv[1];
    file = fopen(filename,"r");
    while ( fscanf(file, "%d %d %d\n", &u,&v,&w) != EOF){
        g.nedges ++;
        g.nvertices = max(g.nvertices, max(u+1,v+1));
        Edgenode *new_node = (Edgenode *) malloc(sizeof(Edgenode));          
        Edgenode *prev = g.edges[u];
        if (g.edges[u] == NULL){
            g.edges[u]          = new_node;
            g.edges[u]->y       = v;
            g.edges[u]-> weight = w;
            g.edges[u]->next    = NULL;
        }
        else{
            while(prev -> next != NULL) prev = prev -> next;
            prev->next          = new_node;
            new_node->y         = v;
            new_node->weight    = w;
            new_node->next      = NULL;
            prev                = new_node;
        }
    }
    fclose(file);
    printf("Number of Vertex: %d, Number of Edges: %d\n", g.nvertices, g.nedges);
    double t1, t2, start, end;
    start = omp_get_wtime();
    omp_set_num_threads(4);
    #pragma omp parallel shared(dist1, g)
    {
        #pragma omp for
        for(int i = 0; i < g.nvertices; i++){
            int * processed = malloc(sizeof(int) * MAX_SIZE);
            dijkstra(processed, &g, i, dist1);
        }
    }
    end = omp_get_wtime();
    t1 = (end - start);
    start = omp_get_wtime();
    omp_set_num_threads(4);
    #pragma omp parallel shared(dist2, g)
    {
        #pragma omp for
        for(int i = 0; i < g.nvertices; i++){
            int * processed = malloc(sizeof(int) * MAX_SIZE);
            dijkstra_optimal(processed, &g, i, dist2);
        }
    }
    end = omp_get_wtime();
    t2 = (end - start);
    printf("run time of orginal dijsktra: %lf\n",t1);
    printf("run time of dijsktra with heap: %lf\n",t2);
    return 0;
}
