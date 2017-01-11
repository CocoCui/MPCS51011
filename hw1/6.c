#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int main() {  
    struct tm b;
    b.tm_year = 93;
    b.tm_mon = 6;
    b.tm_mday = 18;
    b.tm_hour = 19;
    b.tm_min = 0;
    b.tm_sec = 0;
    printf("%s\n", asctime(&b));
    return 0;
}
