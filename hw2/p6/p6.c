#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>
#include <string.h>
#define SEQ_NUM 68

// orginal data
double *q[100];
int l[100];
double max = -DBL_MAX, min = DBL_MAX;

// list in figure 2
double* llist;
int ll = 0;
int* idx[100];
int pointer[100];

// list in figure 3
double *l3[100];
int l3_len[100];
int* id3[100][2];

double randDouble(double a, double b) {
    srand((unsigned)time(NULL));  
    double range = a - b, res;
    if(range == 0) return a;
    res = rand() / (double)RAND_MAX;
    return res * range + b;   
}

int bSearch(double* list, double tag, int len) {
    int l = 0, r = len, mid;
    while(l < r) {
        mid = (l + r) / 2;
        if(list[mid] == tag) return mid;
        else if(list[mid] < tag) l = mid + 1;
        else r = mid;
    }
    return r;
}

void input(char* file) {
    int len;
    double data;
    FILE *f = fopen(file, "r");
    for(int i = 0; i < SEQ_NUM; i++) {
        if(fscanf(f, "%d", &len) == EOF) break;
        //printf("line %d with %d data\n", i, len);
        l[i] = len;
        q[i] = malloc(len * sizeof(double));
        for(int j = 0; j < len; j++) {
            if(fscanf(f, "%lf", &data) == EOF) break;
            if(data > max) max = data;
            if(data < min) min = data;
            q[i][j] = data;
        }
    }
    fclose(f);
    return;
}

int* seriresSearch(double target) {
    int *res = malloc(sizeof(int) * SEQ_NUM);
    for(int i = 0; i < SEQ_NUM; i++) {
        res[i] = bSearch(q[i], target, l[i]);
    }
    return res;
}


int findMin() {
    int minseq = -1;
    double minNum = DBL_MAX;
    for(int i  = 0; i < SEQ_NUM; i++) {
        //printf("%d\n", i);
        if(pointer[i] >= l[i]) continue;
        if(q[i][pointer[i]] < minNum) {
            minNum = q[i][pointer[i]];
            minseq = i;
        }
    }
    return minseq;
}

void longlist() {
    int datasize = 0;
    memset(pointer, 0, sizeof(pointer));
    for(int i = 0; i < SEQ_NUM; i++) datasize += l[i];
    llist = malloc(datasize * sizeof(double));
    for(int i = 0; i < SEQ_NUM; i++) idx[i] = malloc(datasize * sizeof(int));
    int minseq = findMin();
    double minnum;
    do {
        minnum = q[minseq][pointer[minseq]];
        llist[ll] = minnum;
        for(int i = 0; i < SEQ_NUM; i++) {
            if(pointer[i] >= l[i]) {
                idx[i][ll] = l[i];
                continue;
            }
            if(q[i][pointer[i]] == minnum) {
                idx[i][ll] = pointer[i]++;
            }
            else {
                idx[i][ll] = pointer[i];
            }
        }
        ll++;
        minseq = findMin();
    }
    while(minseq != -1);
    return;
}

void printl() {
    for(int i =0; i < ll; i++)
        printf("%.1lf ", llist[i]);
    printf("\n");
    for(int i = 0; i < SEQ_NUM; i++){
        for(int j =0 ; j < ll; j++) {
            printf("%d   ",idx[i][j]);
        }
        printf("\n");
    }

}

int* lookUpLL(double target) {
    int* res = malloc(sizeof(int) * SEQ_NUM);
    int id = bSearch(llist, target, ll);
    if(id >= ll) {
        for(int i = 0; i < SEQ_NUM; i++) res[i] = l[i];
        return res;
    }
    for(int i = 0; i < SEQ_NUM; i++) res[i] = idx[i][id];
    return res;
}



void list3() {
    int sn = SEQ_NUM - 1;
    l3[sn] = malloc(sizeof(double) * l[sn]);
    id3[sn][0] = malloc(sizeof(int) * l[sn]);
    id3[sn][1] = malloc(sizeof(int) * l[sn]);
    l3_len[sn] = l[sn]; 
    for(int i = 0; i < l[sn]; i++) {
        l3[sn][i] = q[sn][i];
        id3[sn][0][i] = i;
        id3[sn][1][i] = 0;
    }
    for(int j = sn - 1; j >= 0; j--) {
        l3[j] = malloc(sizeof(double) * (l3_len[j+1]/2 + l[j]));
        id3[j][0] = malloc(sizeof(int) * (l3_len[j+1]/2 + l[j]));
        id3[j][1] = malloc(sizeof(int) * (l3_len[j+1]/2 + l[j]));
        l3_len[j] = l3_len[j+1]/2 + l[j];
        int id = 0, id0 = 0, id1 = 1;
        while(id0 < l[j] || id1 < l3_len[j+1]) {
            if(id0 >= l[j]) {
                l3[j][id] = l3[j+1][id1];
                id3[j][0][id] = id0;
                id3[j][1][id] = id1;
                id1 += 2;
            } else if(id1 >= l3_len[j+1]) {
                l3[j][id] = q[j][id0];
                id3[j][0][id] = id0;
                id3[j][1][id] = id1;
                id0 += 1;
            } else {
                if(q[j][id0] < l3[j+1][id1]) {
                    l3[j][id] = q[j][id0];
                    id3[j][0][id] = id0;
                    id3[j][1][id] = id1;
                    id0 += 1;
                } else {
                    l3[j][id] = l3[j+1][id1];
                    id3[j][0][id] = id0;
                    id3[j][1][id] = id1;
                    id1 += 2;
                }
            }
            id ++;
        }
    }
    return;
}

void printl3() {
    for(int i = 0; i < SEQ_NUM; i++) {
        for(int j = 0; j < l3_len[i]; j++) printf("%.1lf ", l3[i][j]);
        printf("\n");
        for(int j = 0; j < l3_len[i]; j++) printf("%d   ", id3[i][0][j]);
        printf("\n");
        for(int j = 0; j < l3_len[i]; j++) printf("%d   ", id3[i][1][j]);
        printf("\n");
        printf("\n");
    }

}

int* lookUpL3(double target) {
    int* res = malloc(sizeof(int) * SEQ_NUM);
    int nid = bSearch(l3[0], target, l3_len[0]);
    if(nid >= l3_len[0]) {
        res[0] = l[0];
    }
    else res[0] = id3[0][0][nid];
    for(int i = 1; i < SEQ_NUM; i++) {
        //printf("%d : %d : %d\n", i, nid, id3[i-1][1][nid]);
        if(nid < l3_len[i-1]) nid = id3[i-1][1][nid] - 1;
        else nid = l3_len[i];
        if(nid >= l3_len[i] - 1) {
            nid = l3_len[i] - 1;
            if(target > l3[i][l3_len[i] - 1]) {
                res[i] = l[i];
                nid ++;
            }
            else res[i] = id3[i][0][nid];
        } else {
            if(target <= l3[i][nid]){
                res[i] = id3[i][0][nid];
                nid = id3[i][1][nid];
            }
            else {
                nid ++;
                res[i] = id3[i][0][nid];
                nid = id3[i][1][nid];
            }
        }
    }
    //for(int i = 0; i < SEQ_NUM; i++) printf("%d ", res[i]);
    //printf("\n");
    return res;
}

double randomSearch(int tot, double *targets, int* (*searchfunc)(double target)) {
    time_t begin, end;
    begin = clock();
    for(int i = 0; i < tot; i++) {
        searchfunc(targets[i]);
    }
    end = clock();
    double time = (end - begin) / 1000000.0;
    return time;
}

double* genDoubleList(int tot) {
    double *res = malloc(sizeof(double) *tot);
    for(int i = 0; i <tot; i++) res[i] = randDouble(max, min);
    return res;

}

void freeAll() {
    free(llist);
    for(int i = 0; i < SEQ_NUM; i++) {
        free(q[i]);
        free(l3[i]);
        free(id3[i][0]);
        free(id3[i][1]);
        free(idx[i]);
    }
    return;
}

int main() {
    input("arrays.txt");
    time_t begin, end;
    double time;
    int memory;
    //budilding look up table in figure 2
    begin = clock();
    longlist();
    end = clock();
    time = (end - begin) / 1000000.0;
    printf("Runtime for building look up table in Figure 2: %lf\n", time);
    memory = ll * sizeof(double) + ll * sizeof(int) * SEQ_NUM;
    memory /= 1024; 
    printf("Memory for look up table in Figure 2: %dKB.\n\n", memory);
    
    //building look up table in figure 3
    begin = clock();
    list3();
    end = clock();
    int size = 10000000;
    time = (end - begin) / 1000000.0;
    printf("Runtime for building look up table in Figure 3: %lf\n", time);
    memory = 0;
    for(int i = 0; i <SEQ_NUM; i++) memory += (l3_len[i] * sizeof(double) * 2 + l3_len[i] * sizeof(int) * 2 );
    memory /= 1024;
    printf("Memory for look up table in Figure 3: %dKB.\n\n", memory);
    double* targets = genDoubleList(size);
    double t1, t2, t3;
    t1 = randomSearch(size, targets, seriresSearch);
    t2 = randomSearch(size, targets, lookUpLL);
    t3 = randomSearch(size, targets, lookUpL3);
    printf("Performance for %d random query:\n", size);
    printf("Binary search in each array: %lf\n", t1);
    printf("Speed up with table in Figure 2: %lf\n", t2);
    printf("Speed up with table in Figure 3: %lf\n", t3);
    freeAll();
    return 0;
}
