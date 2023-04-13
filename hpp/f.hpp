

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//--------------------------------------------------

#define nullptr NULL

//--------------------------------------------------

typedef enum Command_code {

    CC_UNKNOWN = 0,

    CC_INSERT,
    CC_SUM,

} Command_code;

//--------------------------------------------------


typedef struct Node_info {

    int key;
    int priority;

} Node_info; const size_t NODE_INFO_SIZE = sizeof (Node_info);


typedef struct Node {

    int key;
    int priority;

    int subtree_sum;

    struct Node* left;
    struct Node* right;

} Node; const size_t NODE_SIZE = sizeof (Node);


typedef struct Treap { // предполагается, что в дереве не хранятся нулевые ключи

    Node* root;

} Treap; const size_t TREAP_SIZE = sizeof (Treap);


typedef struct Node_pair {

    Node* left;
    Node* right;

} Node_pair; const size_t NODE_PAIR_SIZE = sizeof (Node_pair);


typedef struct Find_result {

    int key;
    bool found;

} Find_result; const size_t FIND_RESULT_SIZE = sizeof (Find_result);


//--------------------------------------------------


int          treap_solve       (void);
Command_code get_command_code  (char* cmd); 

Treap* treap_ctor (void);
int    treap_dtor (Treap* tree);
int    node_dtor  (Node* node);

int treap_push (Treap* tree, Node_info info);

Node* create_node (Node_info info);

int node_repair_subtree_sum (Node* node);
int get_subtree_sum         (Node* node);

Node_pair treap_split          (Treap* tree, int key);
Node_pair node_split           (Node*  node, int key);
Node_pair node_split_big_key   (Node*  node, int key);
Node_pair node_split_small_key (Node*  node, int key);

Node* node_merge           (Node_pair pair);
Node* node_merge_top_left  (Node_pair pair);
Node* node_merge_top_right (Node_pair pair);

int treap_sum_lr       (Treap* tree,     int l, int r);
int node_sum_lr        (Node** node_ptr, int l, int r);


int treap_print  (Treap* tree);
int node_print   (Node*  node);
int get_value    (Node*  node);


bool treap_exists (Treap* tree, int key);
bool node_exists  (Node* node,  int key);