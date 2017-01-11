#include "dic.h"
void cmd(Dictionary* d) {
    char* hf[3] = {"BKDRHash", "SUMHash", "DJBHash"};
    d -> t =  malloc(sizeof(Hashtable));
    d -> t -> logfile = fopen("log.txt", "w");
    intial(d -> t, 131, "BKDRHash", BKDRHash);
    while(1) {
        char* w = malloc(sizeof(char) * 1024);
        char* key = malloc(sizeof(char) * 1024);
        char* key2 = malloc(sizeof(char) * 1024);
        char* val = malloc(sizeof(char) * 4096);
        int num;
        printf("\nCommand:");
        scanf("%s", w);
        
        if(strcmp(w,"insert") == 0) {
            scanf("%s", key);
            while(getchar() != '"');
            int id = 0;
            char c;
            while((c = getchar()) != '"') val[id++] = c;
            val[id] = '\0';
            int insertRes = insert(d -> t, key, val, 1);
            if(insertRes) printf("INSERT: %s : %s\n", key, val);
            else printf("INSERT FAILED(DUPLICATED KEY)\n");
        }
        else if(strcmp(w,"delete") == 0){
            scanf("%s", key);
            int deleteRes = delete(d -> t, key);
            if(deleteRes) printf("DELETE: %s\n", key);
            else printf("DELETE FAILED(KEY NOT FOUND)\n");
        }
        else if(strcmp(w,"find") == 0){
            scanf("%s", key);
            scanf("%s", key2);
            findWords(d -> t, key, key2);
        }
        else if(strcmp(w,"print") == 0){
            travel(d -> t);
        }
        else if(strcmp(w,"rehash") == 0){
            int bn, hfn;
            printf("\nNUmber of bins:");
            scanf("%d", &bn);
            printf("Choose the Hash Function(type the index in [1,3]):\n 1.%s\n 2.%s\n 3.%s\n", hf[0], hf[1], hf[2]);
            scanf("%d", &hfn);
            if(hfn == 1) reHash(d -> t, bn, "BKDRHash", BKDRHash);
            else if(hfn == 2) reHash(d -> t, bn, "SUMHash", SUMHash);
            else if(hfn == 3) reHash(d -> t, bn, "DJBHash", DJBHash);
        }
        else if(strcmp(w,"quit") == 0) {
            fclose(d -> t -> logfile);
            break;
        }
        else if(strcmp(w,"read") == 0) {
            scanf("%s", w);
            FILE * file = fopen(w, "r");
            while(fscanf(file, "%s", key) > 0) {
                while(getc(file) != '"');
                int id = 0;
                char c;
                while((c = getc(file)) != '"') val[id++] = c;
                val[id] = '\0';
                int insertRes = insert(d -> t, key, val, 1);
                if(insertRes) printf("INSERT: %s : %s\n", key, val);
                else printf("INSERT %s FAILED(DUPLICATED KEY)\n", key);
            }
        }
        else{
            printf("unknow command.\n");
        }
    }
    return;
}

int main() {
    Dictionary* d;
    d = malloc(sizeof(Dictionary));
    cmd(d);
}
