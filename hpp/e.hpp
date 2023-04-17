

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


typedef enum SON_TYPE {

    LEFT_SON,
    RIGHT_SON

} SON_TYPE;


//--------------------------------------------------


const size_t STRING_LEN = 600;


//--------------------------------------------------


typedef struct Node {

    char* key; // сортируем по ключам!
    char* value;

    struct Node* left;
    struct Node* right;
    struct Node* parent;

} Node; const size_t NODE_SIZE = sizeof (Node);


typedef struct Splay {

    Node* root;

} Splay; const size_t SPLAY_SIZE = sizeof (Splay);

//--------------------------------------------------


int splay_solve (void);

Splay* splay_ctor (void);
int    splay_dtor (Splay* tree);
int    node_dtor  (Node*  node);

int      splay_push         (Splay* tree,     const char* key, const char* value);
int      splay_update_root  (Splay* tree);
int      node_push          (Node** node_ptr, const char* key, const char* value, Node* parent);
int      create_node        (Node** node_ptr, const char* key, const char* value, Node* parent);
SON_TYPE get_son_type       (Node*  node);
int      splay              (Node*  node);
int      rotate_root        (Node*  node);
int      zig_zig            (Node*  node);
int      zig_zag            (Node*  node);
int      small_left_rotate  (Node*  node);
int      small_right_rotate (Node*  node);

char* splay_find (Splay* tree, char* key);
char* node_find  (Node*  node, char* key);

int         splay_print (Splay* tree);
int         node_print  (Node*  node, size_t depth);
int         print_tabs  (size_t depth);
const char* get_key     (Node* node);