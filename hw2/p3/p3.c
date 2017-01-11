#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
// Write array of number of iterations to file
#define WRITE_RESULT

#define MAXDIM 2048
int DIM;

// Maximum number of iterations
#define MAX_ITER 10000

// Domain boundaries
#define XMIN -2
#define XMAX 1
#define YMIN -1.5
#define YMAX 1.5

// Complex number
typedef struct complex_{
  double real;
  double imag;
} Complex;

double mandelbrot_serial();
double mandelbrot_omp_dynamic(int nt);
double mandelbrot_omp_static(int nt);

int main(int argc, char **argv){
    double time_s, time_omp_s[100], time_omp_d[100];
    int thn = omp_get_max_threads();
    for(DIM = 64; DIM <= MAXDIM; DIM *= 2) {
        printf("Size: %d * %d\n", DIM, DIM);
        time_s = mandelbrot_serial();
        for(int i = 1; i <= thn; i++) {
            time_omp_s[i] = mandelbrot_omp_static(i);
            time_omp_d[i] = mandelbrot_omp_dynamic(i);
        }
        printf("Serial: %lf seconds\n", time_s);
        printf("Static Scheduled FOR loop in OpenMP:\n");
        printf("ThreadNum:\t");
        for(int i = 1; i <= thn; i++) printf("%d\t", i);
        printf("\nRunTime:\t");
        for(int i = 1; i <= thn; i++) printf("%.6lf\t", time_omp_s[i]);
        printf("\nSpeed up:\t");
        for(int i = 1; i <= thn; i++) printf("%.4lf\t", time_s / time_omp_s[i]);
        printf("\nDynamic Schedule FOR loop in OpenMP:\n");
        printf("ThreadNum:\t");
        for(int i = 1; i <= thn; i++) printf("%d\t", i);
        printf("\nRunTime:\t");
        for(int i = 1; i <= thn; i++) printf("%.6lf\t", time_omp_d[i]);
        printf("\nSpeed up:\t");
        for(int i = 1; i <= thn; i++) printf("%.4lf\t", time_s / time_omp_d[i]);
        printf("\n\n");
    }
    return 0;
}

double mandelbrot_omp_dynamic(int nt)
{
    int px, py, iter, *U, i=0;
    double tmp;
    Complex c, z;
    // Allocate global array to collect data 
    U = malloc(DIM*DIM*sizeof(int));
    double tick = omp_get_wtime();
    omp_set_num_threads(nt);
    #pragma omp parallel private(px,py, c, z, iter, tmp) firstprivate(DIM)
    {
        #pragma omp for schedule(dynamic)
        for(px = 0; px < DIM; px++){
          for(py = 0; py < DIM; py++){
              c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
              c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
              z.real = 0;
              z.imag = 0;
              iter = 0;
              while(z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                  tmp = z.real*z.real - z.imag*z.imag + c.real;
                  z.imag = 2*z.real*z.imag + c.imag;
                  z.real = tmp;
                  iter++;
              }
              U[ px * DIM + py] = iter;
          }
        }
    }
    double tock = omp_get_wtime();
    #ifdef WRITE_RESULT
    FILE* f;
    if((f = fopen("results_omp.txt", "w")) == NULL){
        printf("Error opening file for writing.\n");
        exit(1);
    }
    int size = DIM;
    fprintf(f, "%d\n", size);
    size = MAX_ITER;
    fprintf(f, "%d\n", size);
    for(py=0; py<DIM; py++){
        for(px=0; px<DIM; px++){
            fprintf(f, "%d ", U[DIM*px + py]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    #endif
    free(U);
    return tock-tick; 
}

double mandelbrot_omp_static(int nt)
{
    int px, py, iter, *U, i=0;
    double tmp;
    Complex c, z;
    // Allocate global array to collect data 
    U = malloc(DIM*DIM*sizeof(int));
    double tick = omp_get_wtime();
    omp_set_num_threads(nt);
    #pragma omp parallel private(px,py, c, z, iter, tmp) firstprivate(DIM)
    {
        #pragma omp for schedule(static)
        for(px = 0; px < DIM; px++){
          for(py = 0; py < DIM; py++){
              c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
              c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
              z.real = 0;
              z.imag = 0;
              iter = 0;
              while(z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
                  tmp = z.real*z.real - z.imag*z.imag + c.real;
                  z.imag = 2*z.real*z.imag + c.imag;
                  z.real = tmp;
                  iter++;
              }
              U[ px * DIM + py] = iter;
          }
        }
    }
    double tock = omp_get_wtime();
    free(U);
    return tock-tick; 
}

double mandelbrot_serial()
{

    int px, py, iter, *U, i=0;
    double tmp;
    Complex c, z;
    // Allocate global array to collect data 
    U = malloc(DIM*DIM*sizeof(int));
    double tick = omp_get_wtime();
    for(px=0; px<DIM; px++){
      for(py=0; py<DIM; py++){
          c.real = XMIN + px*(XMAX - XMIN)/(double)DIM;
          c.imag = YMIN + py*(YMAX - YMIN)/(double)DIM;
          z.real = 0;
          z.imag = 0;
          iter = 0;
          while(z.real*z.real + z.imag*z.imag < 4 && iter < MAX_ITER){
              tmp = z.real*z.real - z.imag*z.imag + c.real;
              z.imag = 2*z.real*z.imag + c.imag;
              z.real = tmp;
              iter++;
          }
          U[px*DIM + py] = iter;
      }
    }
    double tock = omp_get_wtime();
    #ifdef WRITE_RESULT
    FILE* f;
    if((f = fopen("results.txt", "w")) == NULL){
        printf("Error opening file for writing.\n");
        exit(1);
    }
    int size = DIM;
    fprintf(f, "%d\n", size);
    size = MAX_ITER;
    fprintf(f, "%d\n", size);
    for(py=0; py<DIM; py++){
        for(px=0; px<DIM; px++){
            fprintf(f, "%d ", U[DIM*px + py]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
    #endif
    free(U);
    return tock-tick; 
}

