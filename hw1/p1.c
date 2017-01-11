#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int i, a, b[4], c = 0x000000ff, res;
    a = atoi(argv[1]);
    for(i = 0; i < 4; i++) {
        b[i] = a & c;
        c = c << 8;
    }
    res = (b[0] << 24) | (b[1] << 8) | ((b[2] >> 8) & 0x0000ff00) | ((b[3] >> 24) & 0x00000ff);
    printf("%d\n", res);
    return 0;
}
