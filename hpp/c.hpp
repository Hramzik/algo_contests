

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
    CC_DELETE,
    CC_EXISTS,
    CC_NEXT,
    CC_PREV,
    CC_KTH,
} Command_code;

//--------------------------------------------------


typedef struct Node_info {

    int key;
    int priority;

} Node_info; const size_t NODE_INFO_SIZE = sizeof (Node_info);


typedef struct Node {

    int key;
    int priority;

    size_t subtree_size;

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
int          apply_command     (Treap* tree, Command_code code, int argument); 
int          find_result_print (Find_result result); 
int          bool_print        (bool arg); 
Command_code get_command_code  (char* cmd); 

Treap* treap_ctor (void);
int    treap_dtor (Treap* tree);
int    node_dtor  (Node* node);

int treap_push (Treap* tree, Node_info info);
int treap_pop  (Treap* tree, int key);

Node* create_node (Node_info info);

int    node_repair_subtree_size (Node* node);
size_t get_subtree_size         (Node* node);

Node_pair treap_split          (Treap* tree, int key);
Node_pair node_split           (Node*  node, int key);
Node_pair node_split_big_key   (Node*  node, int key);
Node_pair node_split_small_key (Node*  node, int key);

Node* node_merge           (Node_pair pair);
Node* node_merge_top_left  (Node_pair pair);
Node* node_merge_top_right (Node_pair pair);

bool        treap_exists   (Treap* tree, int key);
bool        node_exists    (Node*  node, int key);
Find_result treap_find_jae (Treap* tree, int key);
Find_result node_find_jae  (Node*  node, int key);
Find_result treap_find_jbe (Treap* tree, int key);
Find_result node_find_jbe  (Node*  node, int key);
Find_result treap_find_kth (Treap* tree, size_t k);
Find_result node_find_kth  (Node*  node, size_t k);

int treap_print  (Treap* tree);
int node_print   (Node*  node);
int get_value    (Node*  node);
