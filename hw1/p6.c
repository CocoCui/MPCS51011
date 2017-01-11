#include <stdlib.h>
#include <stdio.h>

double ***d3darr(size_t l, size_t m, size_t n);

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]), i, j, k;
    double ***m = d3darr(n, n, n);
    double count = 0;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++) 
            for(k = 0; k < n; k++) 
                m[i][j][k] = count ++;
    printf("Matrix with 1D indexing:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(k = 0; k < n; k++) printf("%.1f ", m[0][0][i * n * n + j * n + k]);
            printf("\n");
        }
        printf("\n");
    }
    printf("Matrix with 3D indexing:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(k = 0; k < n; k++) printf("%.1f ", m[i][j][k]);
            printf("\n");
        }
        printf("\n");
    }

    free(m);

    return 0;

}


double ***d3darr(size_t l, size_t m, size_t n) {
    double ***matrix;
    double **vec2d;
    double *vec1d;
    int i, j;
    matrix = (double ***) malloc( l * sizeof(double**) + l * m * sizeof(double*) + l * m * n * sizeof(double));
    vec2d = (double**) (matrix + l);
    vec1d = (double*) (vec2d + l * m);
    for(i = 0; i < l; i++) {
        matrix[i] = vec2d + i * m;
        for(j = 0; j < m; j++) matrix[i][j] = vec1d + i * m *  l + j * n;
    }
    return matrix;
}
