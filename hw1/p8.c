#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void alphabetize(char *text[], int nlines);
int part(char *text[], int l, int r);
void quickSort(char *text[], int l, int r);
void bubbleSort(char *text[], int nlines);

int main() {
    int ln = 0, i;
    size_t len = 200, r;
    char *text[500];
    for(i = 0; i < 500; i++) text[i] = malloc(sizeof(char)*len);
    while((r = getline(&text[ln], &len, stdin)) != -1) {
        ln ++;
    }
    alphabetize(text, ln);
    for(i = 0; i < ln; i++) {
        printf("%s", text[i]);
    }
    for(i = 0; i < 500; i++) free(text[i]);
    return 0;
}

void bubbleSort(char *text[], int nlines) {
    int i,j;
    for(i = 0; i < nlines - 1; i++) {
        for(j = 0; j < nlines - 1 - i; j++) {
            if(strcmp(text[j], text[j+1]) > 0) {
                char* temp = text[j+1];
                text[j+1] = text[j];
                text[j] = temp;
            }
        }
    }
    return;
}

int part(char *text[], int l, int r) {
    int i = l, j;
    char* p = text[r], *temp  = NULL;
    for(j = l; j < r; j++) {
        if(strcmp(text[j], p) < 0) {
            temp = text[j];
            text[j] = text[i];
            text[i] = temp;
            i ++;
        }
    }
    temp = text[r];
    text[r] = text[i];
    text[i] = temp;
    return i;
}
/*
 * https://en.wikipedia.org/wiki/Quicksort
 */

void quickSort(char *text[], int l, int r) {
    if(l < r) {
        int p = part(text, l, r);
        quickSort(text, l, p - 1);
        quickSort(text, p + 1, r);
    }
    return;
}

void alphabetize(char *text[], int nlines) {
    quickSort(text, 0, nlines - 1);
    return;

}

