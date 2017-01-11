#ifndef _DIC_
#define _DIC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
typedef struct dict {
    Hashtable* t;
}Dictionary;

void cmd(Dictionary* d);

#endif

