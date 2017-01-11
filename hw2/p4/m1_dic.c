#include "m1.h"
#include "dic.h"

int main() {
    Dictionary d;
    d.intial = intial_m1;
    d.travel = travelInOrder_m1;
    d.insert = insert_m1;
    d.delete = deleteNode_m1;
    d.find = find_m1;
    d.height = height_m1;
    d.treeType = "Model_1_BST";
    d.freeTree = freeTree_m1;
    d.root = d.intial();
    cmd(&d);
    return 0;
}
