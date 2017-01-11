#include "m2.h"
#include "dic.h"

int main() {
    Dictionary d;
    d.intial = intial_m2;
    d.travel = travelInOrder_m2;
    d.insert = insert_m2;
    d.delete = deleteNode_m2;
    d.find = find_m2;
    d.height = height_m2;
    d.treeType = "Model_2_BST";
    d.freeTree = freeTree;
    d.root = d.intial();
    cmd(&d);
    return 0;
}

