#include <stdio.h>
#include <time.h>

#define M 1000
#define N 1000
double A[M][N];
double **dmatrix_distributed(size_t m, size_t n);
double **dmatrix_contiguous(size_t m, size_t n);
void work_kernel_static(double U[M][N], int m, int n);
void work_kernel_dynamic(double **U, int m, int n);

int main(int argc, char * argv[])
{
	
	int i, j, num = 0;
    double **C = dmatrix_distributed(M, N), **B = dmatrix_contiguous(M, N);
    clock_t start, end;
    double ta, tb, tc;
	/* Declare and allocate your arrays A,B,C */
	
	/* Initialize arrays */
    for(i = 0; i < M; i++)
        for(j = 0; j < N; j++) {
            A[i][j] = num;
            B[i][j] = num;
            C[i][j] = num;
            num += 1;
        } 

	/* time A */
    start = clock();
	work_kernel_static( A, M, N);
    end = clock();
    ta = (double)(end - start)/ CLOCKS_PER_SEC;

	/* time B */
    start = clock();
	work_kernel_dynamic( B, M, N);
    end = clock();
    tb = (double)(end - start) / CLOCKS_PER_SEC;

	/* time C */
    start = clock();
	work_kernel_dynamic( C, M, N);
    end = clock();
    tc = (double)(end - start) / CLOCKS_PER_SEC;

	/* Print out timing to stdout in seconds for each array */
    printf("%f\n%f\n%f\n", ta, tb, tc);

	/* Free memory*/
    free(B);
    free(C);
	
	return 0;

}

double **dmatrix_distributed(size_t m, size_t n) {
    double **matrix;
    int i;
    matrix = (double **) malloc( m * sizeof(double* ));
    for(i = 0; i < m; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
    }
    return matrix;
}

double **dmatrix_contiguous(size_t m, size_t n) {
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

void work_kernel_dynamic(double **U, int m, int n) {
	int i,j;
	double a = 1.0, b = 0.5, c;
	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++) {
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}
	return;
}

void work_kernel_static(double U[M][N], int m, int n) {
	int i,j;
	double a = 1.0, b = 0.5, c;
	for( i=1; i < (m-1); i++)
		for( j=1; j < (n-1); j++) {
			c = ( a * (U[i+1][j] + U[i-1][j]) ) +
		            ( b * (U[i][j+1] + U[i][j-1]) ) +
	                    ( (1 - (2*a) - (2*b)) * U[i][j] );
		}
	return;
}
