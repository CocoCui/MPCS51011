#include "dic.h"

char* genString(int len) {
    char *res = malloc(sizeof(char) * len + 1);
    res[len] = '\0';
    for(int i = 0; i < len; i++) res[i] = rand() % 26 + 'a';
    return res;
}

void insert(char *key, char* val, Dictionary *d) {
    int res = d->insert(key, val, &(d -> root));
    if(res == -1) printf("Add failed, the key and value can't be NULL.\n");
    else if(res == 0) printf("Add %s failed, the word already exists.\n", key);
    else printf("Add %s successfully.\n", key);
    return;
}

void travel(Dictionary *d) {
    int id = 0;
    d->travel(d -> root, &id);
    return;
}

char* find(char* key, Dictionary *d) {
    if(key == NULL) {
        printf("Failed, the key can't be NULL.\n");
        return NULL;
    }
    char *res = d -> find(d -> root, key);
    if(res == NULL) {
        printf("Word %s is not in the dictionary.\n", key);
        return NULL;
    } else {
        printf("Word: %s, Definition: %s\n", key, res);
        return res;
    }
}

void delete(char* key, Dictionary *d) {
    if(key == NULL) {
        printf("Failed, the key can't be NULL.\n");
        return;
    }
    int res = d -> delete(key, &(d -> root));
    if(res == 0) printf("Word %s is not found.\n", key);
    else printf("Delete %s successfully.\n", key);
    return;
}

void height(Dictionary *d) {
    printf("The height of %s is %d.\n", d -> treeType, d -> height(d -> root));
    return;
}

void cmd(Dictionary *d) {
    while(1) {
        char* w = malloc(sizeof(char) * 1024);
        char* key = malloc(sizeof(char) * 1024);
        char* val = malloc(sizeof(char) * 4096);
        int num;
        scanf("%s", w);
        
        if(strcmp(w,"add") == 0) {
            scanf("%s", key);
            while(getchar() != '"');
            int id = 0;
            char c;
            while((c = getchar()) != '"') val[id++] = c;
            val[id] = '\0';
            insert(key, val, d);
        }
        else if(strcmp(w,"delete") == 0){
            scanf("%s", key);
            delete(key, d);
        }
        else if(strcmp(w,"find") == 0){
            scanf("%s", key);
            find(key, d);
        }
        else if(strcmp(w,"print") == 0){
            travel(d);
        }
        else if(strcmp(w,"quit") == 0) {
            d -> freeTree(d -> root);
            break;
        }
        else if(strcmp(w,"random") == 0) {
            scanf("%d", &num);
            for(int i = 0; i < num; i++) {
                insert(genString(4), genString(20), d);
            }
        }
        else if(strcmp(w,"height") == 0) {
            height(d);
        }
        else{
            printf("unknow command.\n");
        }
    }
    return;
}
