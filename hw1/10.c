#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void alias(void** p1, void** p2) {
    *p1  = *p2;
    return;
}

float randf(float a, float b) {
    srand((unsigned)time(NULL));  
    float range = a - b, res;
    if(range == 0) return a;
    res = rand() / (float)RAND_MAX;
    return res * range + b;   
}
int main() {
    float a = 1.2, b = 2.2;
    float *p1 = &a, *p2 = &b;
    alias(&p1, &p2);
    printf("%f %f\n", *p1, *p2);
    printf("%f \n", randf(-4,1));

}
