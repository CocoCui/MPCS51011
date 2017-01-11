#include <stdlib.h>
#include <stdio.h>

double **dmatrix(size_t m, size_t n);

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), i, j;
    double **m = dmatrix(n, n);
    double count = 0;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) m[i][j] = count ++;
    printf("Matrix with 1D indexing:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) printf("%.1f ", m[0][i * n + j]);
        printf("\n");
    }
    printf("\nMatrix with 2D indexing:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) printf("%.1f ", m[i][j]);
        printf("\n");
    }
    free(m);
    return 0;

}


/*
 https://niallpjackson.wordpress.com/2013/06/21/contiguous-dynamic-multidimensional-arrays-in-c/
*/

double **dmatrix(size_t m, size_t n) {
    double **matrix;
    double *vec;
    int i;
    matrix = (double **) malloc( m * sizeof(double*) + m * n * sizeof(double));
    vec = (double*) (matrix + m);
    for(i = 0; i < m; i++) {
        matrix[i] = (double*)(vec + n * i);
    }
    return matrix;
}
