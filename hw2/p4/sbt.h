#ifndef _SBT_
#define _SBT_

#include "basic.h"

Node* intial_sbt();

/* find a node with a key
 * return the value of that key otherwise return NULL
 */
char* find_sbt(Node *n, char* key);

/* print all thye keys and values in the tree in an increasing order
 */
void travelInOrder_sbt(Node* n, int* idx);

/* inetert a node to the tree
 * -1 NULL key or NULL value
 * 0 already in dictionary
 * 1 add successfully
 */
int insert_sbt(char* key, char* val, Node **root);

/* delete a node with a key
 * 0 node not found
 * 1 node delete successfully
 */
int deleteNode_sbt(char* key, Node **rt);

int height_sbt(Node* root);

Node* createNode(char* key, char *val);

/* maintain the size balanced treee
 */

void maintain(Node **rt, int flag);


#endif
