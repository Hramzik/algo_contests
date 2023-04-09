

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


typedef struct Node {

    size_t value;
    size_t height;

    struct Node* left;
    struct Node* right;

} Node; const size_t NODE_SIZE = sizeof (Node);


typedef struct Avl { // предполагается, что в дереве не хранятся нулевые ключи

    Node* root;

} Avl; const size_t AVL_SIZE = sizeof (Avl);

//--------------------------------------------------


int avl_solve        (void);
int case_plus_sr     (Avl* tree, size_t argument, char prev_cmd, int  prev_result);
int case_question_sr (Avl* tree, size_t argument,                int* prev_result);

Avl* avl_ctor  (void);
int  avl_dtor  (Avl* tree);
int  node_dtor (Node* node);

int    avl_push           (Avl*   tree,     size_t value);
int    node_push          (Node** node_ptr, size_t value);
int    create_node        (Node** node_ptr, size_t value);
int    update_height      (Node*  node);
size_t get_height         (Node*  node);
int    rotate_left        (Node** node_ptr);
int    rotate_right       (Node** node_ptr);
int    small_left_rotate  (Node** node_ptr);
int    small_right_rotate (Node** node_ptr);

int avl_ask       (Avl*  tree, size_t value);
int node_find_jae (Node* node, size_t value);

size_t my_max (size_t val1, size_t val2);