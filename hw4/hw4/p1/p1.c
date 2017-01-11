#include "p1.h"
int dist1[MAX_SIZE], dist2[MAX_SIZE];

void swap(int id1, int id2) {
    int temp;
    temp = pos[h[id1].vertex];
    pos[h[id1].vertex] = pos[h[id2].vertex];
    pos[h[id2].vertex] = temp;
    temp = h[id1].vertex;
    h[id1].vertex = h[id2].vertex;
    h[id2].vertex = temp;
    temp = h[id1].dis;
    h[id1].dis = h[id2].dis;
    h[id2].dis = temp;
    return;
}

void insert(int v, int d) {
    heapsize ++;
    h[heapsize].vertex = v;
    h[heapsize].dis = d;
    pos[v] = heapsize;
    int cur = heapsize;
    while(cur > 1 && h[cur].dis < h[cur/2].dis) {
        swap(cur, cur/2);
        cur /= 2;
    }
}

int getMin() {
    int min = h[1].vertex;
    swap(heapsize, 1);
    heapsize --;
    if(heapsize > 0) {
        int cur = 1;
        while(cur * 2 <= heapsize) {
            cur *= 2;
            if(cur < heapsize && h[cur].dis > h[cur + 1].dis) cur ++;
            if(h[cur].dis < h[cur/2].dis) swap(cur, cur/2);
            else break;
        }
    }
    return min;
}

void decrease(int idx, int newdis) {
    h[idx].dis = newdis;
    while(idx > 1 && h[idx].dis < h[idx/2].dis) {
        swap(idx, idx/2);
        idx /= 2;
    }
    return;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void dijkstra(Graph *g, int start, int *distance){
    int v, w, weight, dist, count = 0;
    Edgenode *p;
    int processed[MAX_SIZE+1];
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

void dijkstra_optimal(Graph *g, int start, int *distance){
    int v, w, weight, dist, count = 0;
    Edgenode *p;
    int processed[MAX_SIZE+1];
    for(int i = 0; i < g -> nvertices; i++) {
        processed[i] = 0;
        distance[i] = MAX_INT;
    }
    distance[start] = 0;
    for(int i = 0; i < g -> nvertices; i++) insert(i, distance[i]);
    v = getMin();
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
                decrease(pos[w], distance[w]);
            }
        }
        v = getMin();
        count ++;
    }
    return;
}

void test(Graph *g) {
    time_t begin, end;
    double t1, t2;
    begin = clock();
    dijkstra_optimal(g, 0, dist1);
    end = clock();
    t1 = (end - begin) / 1000000.0;
    printf("run time for single source:\n");
    printf("run time of dijsktra with heap: %lf\n",t1);
    begin = clock();
    dijkstra(g, 0, dist2);
    end = clock();
    t2 = (end - begin) / 1000000.0;
    printf("run time of orginal dijsktra: %lf\n",t2);
    for(int i = 0; i < g -> nvertices; i++) dijkstra_optimal(g, i, dist1);
    end = clock();
    t1 = (end - begin) / 1000000.0;
    printf("run time for all source:\n");
    printf("run time of dijsktra with heap: %lf\n",t1);
    begin = clock();
    for(int i = 0; i < g -> nvertices; i++) dijkstra(g, i, dist2);
    end = clock();
    t2 = (end - begin) / 1000000.0;
    printf("run time of orginal dijsktra: %lf\n",t2);
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
        printf("%d %d %d\n", u,v,w);
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
    time_t begin, end;
    double t1, t2;
    test(&g);
}
