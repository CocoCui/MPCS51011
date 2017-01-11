#include "m2.h"
#include "sbt.h"
#include "dic.h"
#include "m1.h"


void testInsert(int round, int perround, Dictionary *d, void (*freefunc)(Node* r), int unit) {
    double h = 0, t = 0;
    time_t begin, end;
    char** data = malloc(sizeof(char*) * perround);
    for(int i = 0; i < round; i++) {
        for(int j = 0; j < perround; j++) {
            data[j] = genString(10);
        }
        begin = clock();
        for(int j = 0; j < perround; j++) {
            d -> insert(data[j], data[j], &(d -> root));
        }
        end = clock();
        for(int j = 0; j < perround; j++) {
            free(data[j]);
        }
        t = t + (end - begin) / 1000000.0;
        h = h + d -> height(d -> root);
        freefunc(d -> root);
        d -> root = d -> intial(); 
        
    }
    printf("Insertion Test of %s:\n", d -> treeType);
    printf("Average runtime: %f / %d insertions.\n", t / (round * perround) * unit, unit);
    printf("Average height: %f / %d insertions.\n", h / round, perround);
    free(data);
    return;
}

void testFind(int round, int perround, Dictionary *d, void (*freefunc)(Node* r), int unit) {
    double h = 0, t = 0;
    time_t begin, end;
    char** data = malloc(sizeof(char*) * perround);
    int* findList = malloc(sizeof(int) * perround);
    char** randdata = malloc(sizeof(char*) * perround);
    for(int i = 0; i < round; i++) {
        for(int j = 0; j < perround; j++) {
            data[j] = genString(10);
            randdata[j] = genString(10);
            d -> insert(data[j], data[j], &(d -> root));
            findList[j] = rand() % perround;
        }
        begin = clock();
        for(int j = 0; j < perround; j++) {
            d -> find(d -> root, data[findList[j]]);
            d -> find(d -> root, randdata[j]);
        }
        end = clock();
        for(int j = 0; j < perround; j++) {
            free(data[j]);
            free(randdata[j]);
        }
        t = t + (end - begin) / 1000000.0;
        freefunc(d -> root);
        d -> root = d -> intial(); 
        
    }
    printf("Find Test of %s:\n", d -> treeType);
    printf("Average runtime: %f / %d lookup (1/2 hit, 1/2 miss).\n", t / (round * perround * 2) * unit, unit);
    free(data);
    free(findList);
    return;
}


void testDelete(int round, int perround, Dictionary *d, void (*freefunc)(Node* r), int unit) {
    double h = 0, t = 0;
    time_t begin, end;
    char** data = malloc(sizeof(char*) * perround * 5);
    int* delList = malloc(sizeof(int) * perround * 5);
    for(int i = 0; i < round; i++) {
        for(int j = 0; j < perround * 5; j++) {
            data[j] = genString(10);
            d -> insert(data[j], data[j], &(d -> root));
            delList[j] = rand() % (perround * 5);
        }
        begin = clock();
        for(int j = 0; j < perround; j++) {
            d -> delete(data[delList[j]],&(d -> root));
        }
        end = clock();
        for(int j = 0; j < perround; j++) {
            free(data[j]);
        }
        t = t + (end - begin) / 1000000.0;
        freefunc(d -> root);
        d -> root = d -> intial();
    }
    printf("Delete Test of %s:\n", d -> treeType);
    printf("Average runtime: %f / %d detete (delete 1/5 of nodes).\n", t / (round * perround) * unit, unit);
    free(data);
    free(delList);
    return;
}
int main() {
    srand((unsigned)time(NULL));
    //intailize a size balanced tree
    Dictionary d_sbt;
    d_sbt.intial = intial_sbt;
    d_sbt.travel = travelInOrder_sbt;
    d_sbt.insert = insert_sbt;
    d_sbt.delete = deleteNode_sbt;
    d_sbt.find = find_sbt;
    d_sbt.height = height_sbt;
    d_sbt.treeType = "Size_Balanced_Tree";
    d_sbt.root = d_sbt.intial();

    //intailize a model 1 bst
    Dictionary d_m1;
    d_m1.intial = intial_m1;
    d_m1.travel = travelInOrder_m1;
    d_m1.insert = insert_m1;
    d_m1.delete = deleteNode_m1;
    d_m1.find = find_m1;
    d_m1.height = height_m1;
    d_m1.treeType = "Model_1_BST";
    d_m1.root = d_m1.intial();

    //intialize a model 2 bst
    Dictionary d_m2;
    d_m2.intial = intial_m2;
    d_m2.travel = travelInOrder_m2;
    d_m2.insert = insert_m2;
    d_m2.delete = deleteNode_m2;
    d_m2.find = find_m2;
    d_m2.height = height_m2;
    d_m2.treeType = "Model_2_BST";
    d_m2.root = d_m2.intial();
    
    int unit = 1000;
    for(int i = unit; i <= 1000000; i *= 10){
        printf("Number of Opeartions: %d\n", i);
        testDelete(10, i, &d_sbt, freeTree, unit);
        testDelete(10, i, &d_m1, freeTree_m1, unit);
        testDelete(10, i, &d_m2, freeTree, unit);
        printf("\n");
        testInsert(10, i, &d_sbt, freeTree, unit);
        testInsert(10, i, &d_m1, freeTree_m1, unit);
        testInsert(10, i, &d_m2, freeTree, unit);
        printf("\n");
        testFind(10, i, &d_sbt, freeTree, unit);
        testFind(10, i, &d_m1, freeTree_m1, unit);
        testFind(10, i, &d_m2, freeTree, unit);
        printf("\n");
    }

}
