

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------------------------------

#define nullptr NULL

//--------------------------------------------------

typedef struct Node_info {

    int value;
    int priority;

} Node_info; const size_t NODE_INFO_SIZE = sizeof (Node_info);


typedef struct Node {

    int value;
    int priority;

    struct Node* left;
    struct Node* right;

} Node; const size_t NODE_SIZE = sizeof (Node);


typedef struct Treap { // предполагается, что в дереве не хранятся нулевые ключи

    Node* root;

} Treap; const size_t TREAP_SIZE = sizeof (Treap);

//--------------------------------------------------


int treap_solve        (void);

Treap* treap_ctor (void);
int    treap_dtor (Treap* tree);
int    node_dtor  (Node* node);

int treap_push      (Treap* tree,     Node_info* info);
int treap_push_root (Treap* tree,     Node_info* info);
int node_push       (Node*  node,     Node_info* info);
int create_node     (Node** node_ptr, Node_info* info);

int treap_print  (Treap* tree);
int node_print   (Node*  node, int parent);
int get_value    (Node*  node);

