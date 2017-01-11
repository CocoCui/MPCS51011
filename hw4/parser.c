#include <stdio.h>
#include <string.h>
#define MAX_CHAR_PER_LINE 10000


int read_file(char* name) {
    FILE* f = fopen(name, "r");
    int linenum = 0, v, u;
    double p;
    size_t r, len = MAX_CHAR_PER_LINE;
    char *line = NULL, *start;
    while((r = getline(&line, &len, f)) != -1) {
        sscanf(line, "%d", &v);
        printf("---%d---%s", v,line);
        start = line;
        while(*start != '[') start ++;
        printf("%s", start);
        sscanf(start, "[%d, %lf]", &u, &p);
        printf("qwd");
        printf("(%d, %lf)", u, p);
        /*while(sscanf(start, "[%d, %lf]", &u, &p)) {
            start ++;
            while(*start != '[') start ++;
            printf("(%d, %lf)", u, p);
        }
        printf("\n");*/
    }
    fclose(f);
    return linenum;
}
int main(int argc, char** argv) {
    int i;
    read_file(argv[1]);
    return 0;
}

