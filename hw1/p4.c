#include <stdlib.h>
#include <stdio.h>

double **dmatrix(size_t m, size_t n);

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), i, j;
    double **m = dmatrix(n, n);
    double count = 0;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) m[i][j] = count ++;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) printf("%.1f ", m[i][j]);
        printf("\n");
    }
    for(i = 0; i < n; i++) free(m[i]);
    free(m);
    return 0;

}

double **dmatrix(size_t m, size_t n) {
    double **matrix;
    int i;
    matrix = (double **) malloc( m * sizeof(double* ));
    for(i = 0; i < m; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    return matrix;
}
