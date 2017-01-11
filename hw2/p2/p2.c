#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#define N 2048

float ** matrix( int n )
{
	float *data = (float *) calloc( n*n, sizeof(float) );
	float **M  = (float **) malloc( n  * sizeof(float*));
    memset(data, 0, sizeof(data));
	for( int i = 0; i < n; i++ )
		M[i] = &data[i*n];

	return M;
}

void matrix_free( float ** M)
{
	free(M[0]);
	free(M);
}

void init(float ** M, int n)
{
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
			M[i][j] = (float) ( rand() % 100 );
}

double mm_omp(int nt, int n)
/* Perform matrix multiplication using OpenMP */
{
    float ** A = matrix(n);
	float ** B = matrix(n);
	float ** C = matrix(n);
	init(A,n);
	init(B,n);

	double start = omp_get_wtime();
	// Multiply
    omp_set_num_threads(nt);
    int i, j, k;
    float sum;
    #pragma omp parallel private(i,j,k,sum), shared(A, B, C, n)
    {
        #pragma omp for
        for( i = 0; i < n; i++ )
            for( k = 0; k < n; k++ )
                for( j = 0; j < n; j++ ){
                    C[i][j] += A[i][k] * B[k][j];
                }
    }
	double stop = omp_get_wtime();
	matrix_free(A);
	matrix_free(B);
	matrix_free(C);
    return stop-start;
}

double mm_serial( int n )
/* Perform matrix multiplication serially */
{

	// Allocate arrays
	float ** A = matrix(n);
	float ** B = matrix(n);
	float ** C = matrix(n);
	init(A,n);
	init(B,n);

	double start = omp_get_wtime();
	// Multiply
	for( int i = 0; i < n; i++ )
		for( int j = 0; j < n; j++ )
			for( int k = 0; k < n; k++ )
				C[i][j] += A[i][k] * B[k][j];
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);

    return stop-start;

}

double mm_serial_opt( int n )
/* Perform matrix multiplication serially */
{

	// Allocate arrays
	float ** A = matrix(n);
	float ** B = matrix(n);
	float ** C = matrix(n);
	init(A,n);
	init(B,n);
	double start = omp_get_wtime();
	// Multiply
	for( int i = 0; i < n; i++ )
		for( int k = 0; k < n; k++ )
			for( int j = 0; j < n; j++ )
				C[i][j] += A[i][k] * B[k][j];
	double stop = omp_get_wtime();

	matrix_free(A);
	matrix_free(B);
	matrix_free(C);

    return stop-start;

}

int main(int argc, char * argv[])
{

    int i,j;
    int n = N;
    double time_s, time_opt, time_omp[100];
    int thn = omp_get_max_threads();
    FILE* file = fopen("p2_speed_up.txt","w");
    /* time serial case  */
    for(int s = 32; s <= N; s *= 2) {
        printf("Matrix Size: %d * %d\n", s, s);
        time_s = mm_serial(s);
        time_opt = mm_serial_opt(s);
        for(i = 1; i <= thn; i++) time_omp[i] = mm_omp(i, s);
        printf("Serial: %lf seconds\n", time_s);
        printf("Serial: %lf seconds(optimal in cache)\n", time_opt);
        printf("ThreadNum:\t");
        for(int i = 1; i <= thn; i++) printf("%d\t", i);
        printf("\nRunTime:\t");
        for(int i = 1; i <= thn; i++) printf("%.4lf\t", time_omp[i]);
        printf("\nSpeed up:\t");
        for(int i = 1; i <= thn; i++) printf("%.4lf\t", time_opt / time_omp[i]);
        for(int i = 1; i <= thn; i++) fprintf(file, "%.4lf ", time_opt / time_omp[i]);
        printf("\n\n");
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;

}


