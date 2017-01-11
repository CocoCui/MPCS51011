#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define M 1024 * 32
#define N 1024 * 32

double work_kernel_omp(int nt,double **U, double **V, int m, int n)
{
    /* Fill in your code here */
    int i,j;
    double a = 1.0, b = 0.5, c;

	double start = omp_get_wtime();
    omp_set_num_threads(nt);
    #pragma omp parallel firstprivate(a,b), private(i,j), shared(n,m,V)
    {
        #pragma omp for
        for( i=1; i < (m-1); i++)
            for( j=1; j < (n-1); j++)
            {
                V[i][j] = ( a * (U[i+1][j] + U[i-1][j]) ) +
                          ( b * (U[i][j+1] + U[i][j-1]) ) +
                          ( (1 - (2*a) - (2*b)) * U[i][j] );
            }
    }
	double stop = omp_get_wtime();

    return stop-start;
}

double work_kernel_serial(double **U, double **V, int m, int n)
{
    int i,j;
    double a = 1.0, b = 0.5, c;

	double start = omp_get_wtime();
    for( i=1; i < (m-1); i++)
        for( j=1; j < (n-1); j++)
        {
            V[i][j] = ( a * (U[i+1][j] + U[i-1][j]) ) +
                      ( b * (U[i][j+1] + U[i][j-1]) ) +
                      ( (1 - (2*a) - (2*b)) * U[i][j] );
        }
	double stop = omp_get_wtime();

    return stop-start;
}

int main(int argc, char * argv[])
{

    int i,j;
    int m = M;
    int n = N;
    double time_s, time_omp[100];

    double *B_block = (double *) malloc(sizeof(double) * m * n);
    double *V_block = (double *) malloc(sizeof(double) * m * n);
    double **B = (double **) malloc(sizeof(double*) * m); 
    double **V = (double **) malloc(sizeof(double*) * m);
    FILE *file = fopen("p1_speed_up.txt", "w");
    for(i=0; i<m; i++){
        B[i] = B_block + n*i; 
        V[i] = B_block + n*i; 
    }

    /* Initialize arrays */
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            B[i][j] = i*n + j;
        }
    }
    int thn = omp_get_max_threads();
    /* time serial case  */
    for(int s = 32; s <= M; s *= 2) {
        printf("\n\nMatrix Size: %d * %d\n", s, s);
        time_s = 0;
        for(int r = 0; r < 10; r ++) time_s += work_kernel_serial(B, V, s, s);
        time_s /= 10;
        for(i = 1; i <= thn; i++) {
            time_omp[i] = 0;
            for(int r = 0; r < 10; r ++) time_omp[i] += work_kernel_omp(i, B, V, s, s);
            time_omp[i] /= 10;
        }
        printf("Serial: %lf seconds\n", time_s);
        printf("ThreadNum:\t");
        for(int i = 1; i <= thn; i++) printf("%d\t", i);
        printf("\nRunTime:  \t");
        for(int i = 1; i <= thn; i++) printf("%.6lf\t", time_omp[i]);
        printf("\nSpeed up:  \t");
        for(int i = 1; i <= thn; i++) printf("%.6lf\t", time_s / time_omp[i]);
        for(int i = 1; i <= thn; i++) fprintf(file, "%.4lf ", time_s / time_omp[i]);
        fprintf(file, "\n");
    }
    fclose(file);
    /* Free memory*/
    free(B_block);
    free(V_block);
    free(B);
    free(V);

    return 0;

}


