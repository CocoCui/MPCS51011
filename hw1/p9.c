#include <stdio.h>
#include <string.h>
#define MAX_LINES 1000
#define MAX_CHAR_PER_LINE 1000

char text[MAX_LINES][MAX_CHAR_PER_LINE];

int read_file(char* name) {
    FILE* f = fopen(name, "r");
    int linenum = 0;
    size_t r, len = MAX_CHAR_PER_LINE;
    char *line = NULL; 

    while((r = getline(&line, &len, f)) != -1) {
        memcpy(text[linenum], line, r);
        linenum ++ ;
    }
    fclose(f);
    return linenum;
}
int main(int argc, char** argv) {
    int i;
    memset(text, 0, sizeof(text));
    read_file(argv[1]);
    for(i = 0; i < MAX_LINES; i++) {
        if(strlen(text[i]) == 0) break;
        printf("%s", text[i]);
    }
    return 0;
}
