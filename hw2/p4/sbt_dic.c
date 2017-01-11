#include "sbt.h"
#include "dic.h"

int main() {
    Dictionary d;
    d.intial = intial_sbt;
    d.travel = travelInOrder_sbt;
    d.insert = insert_sbt;
    d.delete = deleteNode_sbt;
    d.find = find_sbt;
    d.height = height_sbt;
    d.treeType = "Size_Balanced_Tree";
    d.freeTree = freeTree;
    d.root = d.intial();
    cmd(&d);
    return 0;
}

