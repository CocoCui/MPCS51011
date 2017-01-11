#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CHAR_PER_LINE 10000
double q[200][200];
double s[200][200];
int x[10000];
int n;
double p[200];
double randf(double a, double b) {
    double range = a - b, res;
    if(range == 0) return a;
    res = rand() / (double)RAND_MAX;
    return res * range + b;   
}

int max(int a, int b) {
    return a > b ? a : b;
}

int sample(int x) {
    double p = randf(0,1);
    for(int i = 1; i <= n; i++) {
        if(s[x][i] > p) return i;
    }
}

void mc(int num) {
    x[0] = rand() % n + 1;
    p[x[0]] ++;
    for(int i = 1; i < num; i++){
        x[i] = sample(x[i-1]);
        p[x[i]] ++;
    }
    for(int i = 0; i < n; i++) {
        p[i] /= num;
    }
    return;
}

void read_file(char* name) {
    FILE* f = fopen(name, "r");
    int v, u;
    double p;
    size_t r, len = MAX_CHAR_PER_LINE;
    char *line = NULL, *start;
    while((r = getline(&line, &len, f)) != -1) {
        sscanf(line, "%d", &u);
        if(u > n) n = u;
        start = line;
        while(1) {
            while(*start != '[' && *start != '\0') start ++;
            if(*start == '\0') break;
            if(sscanf(start, "[%d, %lf]", &v, &p) == 2) {
                start ++;
                q[u][v] = p;
                s[u][v] = p;
            }    
            else break;
        }
    }
    fclose(f);
    return;
}

void sum() {
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++) 
            s[i][j] += s[i][j-1];
    return;
}

int main(int argc, char** argv) {
    memset(q, 0, sizeof(q));
    read_file( argv[1]);
    sum();
    printf("Stationary Probablity:\n");
    mc(10000);
    for(int i = 0; i < n; i++) {
        printf("%lf ", p[i]);
    }
}

