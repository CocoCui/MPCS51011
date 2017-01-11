#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct wordCount {
    char *word;
    int count;
};

int check(char* word) {
    int i;
    if(strlen(word) < 2) return 0;
    for(i = 0; i < strlen(word) - 1; i++)
        if( word[i] == word[i + 1] ) return 1;
    return 0;
}

void insert(struct wordCount *w, int *s, char* word) {
    int i;
    if(!check(word)) return;
    for(i = 0; i < *s; i++) {
        if(strcmp(w[i].word, word) == 0)  {
            w[i].count ++;
            return;
        }
    }
    w[*s].word = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(w[*s].word, word);
    w[*s].count = 1;
    *s += 1;
    return;
}

void printWords(struct wordCount *w, int s) {
    int i;
    for(i = 0; i < s; i++) {
        printf("%s : %d\n", w[i].word, w[i].count);
    }
    return;
}

void freeWords(struct wordCount *w, int s) {
    int i;
    for(i = 0; i < s; i++) {
        if(w[i].word != NULL) free(w[i].word);
    }
    return;
}

int punctuations(char c) {
    if(c == '.' || c == ';' || c == ':' || c == '?' || c == '-' || c == ',') return 0;
    else return 1;
}

int alpha(char c) {
    if(c >= 'a' && c <= 'z') return 1;
    else if(c >= 'A' && c <= 'Z') return 1;
    else if(c >= '0' && c <= '9') return 1;
    else if(c == 39) return 1;
    else return 0;
}

int filter(char* text, int *l, int *r) {
    int len = strlen(text);
    while(!alpha(text[*l]) && *l < len) (*l)++;
    *r = *l + 1;
    while(alpha(text[*r]) && *r < len) (*r)++;
    if(*l >= len) return 0;
    else return 1;
}

int main(int argc, char** argv) {
    struct wordCount w[1000];
    int c = 0;
    FILE *f = fopen(argv[1], "r");
    char buf[4096];
    char word[4096];
    int l, r;
    while(fscanf(f, "%s", buf) != EOF) {
        l = 0, r = 1;
        while(filter(buf, &l, &r)) {
            if(r > l) {
                strncpy(word, buf + l, r - l);
                word[r - l] = '\0';
                l = r + 1;
                insert(w, &c, word);
            }
        }
    }
    printWords(w, c);
    freeWords(w, c);
}
