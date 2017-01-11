#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){
  struct person{
    char *last, *first;
  } **p1;

  /* include allocation and initialization below */
    p1 = malloc(sizeof(struct person*));
    p1[0] =  malloc(sizeof(struct person));
    p1[0] -> last = malloc(sizeof(char) * 1024);
    p1[0] -> first = malloc(sizeof(char) * 1024);
    p1[0] -> last = "Cui";
    p1[0] -> first = "Yan";
    printf("%s , %s\n", p1[0] -> last, p1[0] -> first);






}
