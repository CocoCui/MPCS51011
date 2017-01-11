#ifndef _M1_
#define _M1_

#include "basic.h"

Node* intial_m1();

/* find a node with a key
 * return the value of that key otherwise return NULL
 */
char* find_m1(Node *n, char* key);

/* print all thye keys and values in the tree in an increasing order
 */
void travelInOrder_m1(Node* n, int* idx);

/* inetert a node to the tree
 * -1 NULL key or NULL value
 * 0 already in dictionary
 * 1 add successfully
 */
int insert_m1(char* key, char* val, Node **root);

/* delete a node with a key
 * 0 node not found
 * 1 node delete successfully
 */
int deleteNode_m1(char* key, Node **rt);

int height_m1(Node *root);

void freeTree_m1(Node* r);
#endif
