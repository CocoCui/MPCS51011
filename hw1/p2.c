#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    float a;
    int bit[32];
    a = atof(argv[1]);
    int *b = (int*)&a;
    int t = *b;
    int mask = 0x00000001, i;
    for(i = 0; i < 32; i++) {
        int curbit = mask & t;
        mask *= 2;
        if(curbit == 0) bit[31 - i] = 0;
        else bit[31 - i] = 1;
    }
    for(i = 0; i < 32; i++) {
        printf("%d", bit[i]);
        if(i == 8 || i == 0) printf(" ");
    }
    printf("\n");
    return 0;
}

