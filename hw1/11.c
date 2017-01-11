#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int i;

void catch_function(int signal){
  printf("segmentation fault at loop index: %d\n",i);
  exit(1);
}

int main() {
    signal(SIGSEGV, catch_function);
    
    char *a;
    for(i = -1; i < 10; i++)
        a[i] = i;
    return 0;
}
