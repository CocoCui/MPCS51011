#include "p3.h"
#include <omp.h>
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

void findMin(int* processed, int* distance, int s, int e, int* md, int* mv) {
    for(int i = s; i < e; i++) {
        if(processed[i] == 0 && distance[i] < *md) {
            *md = distance[i];
            *mv = i;
        }
    }
    return;
}
void dijkstra(Graph *g, int start, int *distance, int nt){
    int v, w, weight, dist, count = 0;
    Edgenode *p;
    int *processed;
    processed = malloc(sizeof(int) * g -> nvertices);
    for(int i = 0; i < g -> nvertices; i++) {
        processed[i] = 0;
        distance[i] = MAX_INT;
    }
    distance[start] = 0;
    v = start;
    int step = g -> nvertices / nt + 1;
    /* add v to processed list and update distance of neighbors */
    while (count < g -> nvertices && processed[v] == 0) {
        processed[v] = 1;
        p = g->edges[v];
        omp_set_num_threads(nt);
        //#pragma omp parallel firstprivate(g) private(w, weight)
        {
            //#pragma omp for schedule(runtime)
            for(int i = 0; i < g -> degree[v]; i++) {
                w = g -> edges[v][i].y;
                weight = g -> edges[v][i].weight;
                if(processed[w]) continue;
                if(distance[w] > (distance[v] + weight)) distance[w] = distance[v] + weight;
            }
        }
        dist = MAX_INT;
        int *min_thread = malloc(sizeof(int) * nt);
        int *v_thread = malloc(sizeof(int) * nt);
        for(int i = 0; i < nt; i++) min_thread[i] = MAX_INT;

        #pragma omp parallel firstprivate(step, processed, min_thread, distance, g)
        {
            #pragma omp for 
            /*for(int i = 0; i < nt; i++) {
                int s = i * step, e = (i + 1) * step;
                if(e > g -> nvertices) e = g -> nvertices;
                int tid = omp_get_thread_num();
                findMin(processed, distance, s, e, min_thread + tid, v_thread + tid);
            }*/
            for (int i = 0; i < g -> nvertices; i++) {
                if ((processed[i] == 0) && ( distance[i] < dist)) {
                    dist = distance[i];
                    v = i;
                }
            }
        }
        /*for(int i =0; i < nt; i++) {
            if(min_thread[i] < dist) {
                dist = min_thread[i];
                v = v_thread[i];
            }
        }*/
        count ++;
    }
    free(processed);
    return;
}

/*void dijkstra_optimal(Graph *g, int start, int *distance){
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
}*/

int main(int argc, char **argv) {
    Graph g;
    Edgenode *e;
    FILE *file;
    char *filename;
    int u,v,w;
    int i;
    int dist1[MAX_SIZE], dist2[MAX_SIZE];
    g.nvertices = 0;
    g.nedges = 0;
    for (i = 0; i < MAX_SIZE;++i){
        g.edges[i] = NULL; 
        g.degree[i] = 0;
    }
    filename = argv[1];
    file = fopen(filename,"r");
    while ( fscanf(file, "%d %d %d\n", &u,&v,&w) != EOF){
        g.nedges ++;
        g.nvertices = max(g.nvertices, max(u+1,v+1));
        g.degree[u] ++;
    }
    fclose(file);
    file = fopen(filename,"r");
    for(int i = 0; i < g.nvertices; i++) {
        g.edges[i] = malloc(sizeof(Edgenode*) * g.degree[i]);
        g.degree[i] = 0;
    }
    while ( fscanf(file, "%d %d %d\n", &u,&v,&w) != EOF){
        Edgenode *new_node = (Edgenode *) malloc(sizeof(Edgenode));
        new_node -> y = v;
        new_node -> weight = w;
        Edgenode *prev = g.edges[u];
        g.edges[u][g.degree[u]] = *new_node;
        g.degree[u] ++;
    }
    fclose(file);
    printf("Number of Vertex: %d, Number of Edges: %d\n", g.nvertices, g.nedges);
    double t1, t2, start, end;
    start = omp_get_wtime();
    for(int i = 0; i < 1; i++) {
        dijkstra(&g, i, dist1, 1);
    }
    end = omp_get_wtime();
    t1 = (end - start);
    start = omp_get_wtime();
    for(int i = 0; i < 1 ; i++) {
        dijkstra(&g, i, dist1, 3);
    }
    end = omp_get_wtime();
    t2 = (end - start);
    printf("run time of orginal dijsktra: %lf\n",t1);
    printf("run time of parallelized dijsktra: %lf\n",t2);
    for(int i = 0; i < g.nvertices; i++) {
        free(g.edges[i]);
    }
    return 0;
}
