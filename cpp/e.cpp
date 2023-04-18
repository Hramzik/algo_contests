

#include "../hpp/e.hpp"


//--------------------------------------------------


int main (void) {

    splay_solve ();


    return 0;
}


int splay_solve (void) {

    Splay* tree = splay_ctor ();


    size_t n                 = 0; assert (scanf ("%zd", &n));
    char   name [STRING_LEN]; // error: variable-sized object may not be initialized  127 |  char   name [STRING_LEN] = "";
    char   car  [STRING_LEN];

    for (size_t i = 0; i < n; i++) {

        scanf ("%s %s", name, car);

        splay_push (tree, name, car); // splay_print (tree);
        splay_push (tree, car, name); // splay_print (tree);
    }


    size_t q                     = 0; assert (scanf ("%zd", &q));
    char   question [STRING_LEN];

    for (size_t i = 0; i < q; i++) {

        scanf ("%s", question);

        printf ("%s\n", splay_find (tree, question));
    }


    splay_dtor (tree);


    return 0;
}



Splay* splay_ctor (void) {

    Splay* tree = (Splay*) calloc (1, SPLAY_SIZE);


    tree->root = nullptr;


    return tree;
}


int splay_dtor (Splay* tree) {

    assert (tree);


    node_dtor (tree->root);


    free (tree);


    return 0;
}


int node_dtor (Node* node) {

    if (!node) return 0;


    if (node->left)  node_dtor (node->left);
    if (node->right) node_dtor (node->right);


    free (node->key);
    free (node->value);


    free (node);


    return 0;
}


int splay_push (Splay* tree, const char* key, const char* value) {

    assert (tree);


    node_push (&tree->root, key, value, nullptr);


    splay_update_root (tree); // node push -> splay -> rotate_root может испортить корень, теперь он сын корня
                              // а при зиг заге корень мог опуститься на два уровня!


    return 0;
}


int splay_update_root (Splay* tree) {

    assert (tree);


    if (tree->root->parent) {

        tree->root = tree->root->parent; // вверх на 1 уровень


        if (tree->root->parent) tree->root = tree->root->parent; // вверх еще на один уровень

    }


    return 0;
}


//--------------------------------------------------
#define cur_node (*node_ptr)
//--------------------------------------------------

int node_push (Node** node_ptr, const char* key, const char* value, Node* parent) { // node_ptr - указатель на поддерево, после выполнения функции в нем есть value, возможны повороты

    assert (node_ptr);


    if (!cur_node) {

        create_node (node_ptr, key, value, parent);
        splay (cur_node);


        return 0;
    }

    // if (cur_node->value == value) return 0;


    if (strcmp (cur_node->key, key) > 0)  {

        node_push (&cur_node->left, key, value, cur_node);


        return 0;
    }


    // cur_node->value < value

    node_push (&cur_node->right, key, value, cur_node);


    return 0;
}


int create_node (Node** node_ptr, const char* key, const char* value, Node* parent) {

    assert (node_ptr);


    cur_node = (Node*) calloc (1, NODE_SIZE);


    cur_node->key   = (char*) calloc (1, STRING_LEN);
    cur_node->value = (char*) calloc (1, STRING_LEN);

    strcpy (cur_node->key,   key);
    strcpy (cur_node->value, value);


    cur_node->left  = nullptr;
    cur_node->right = nullptr;


    cur_node->parent = parent;


    return 0;
}


SON_TYPE get_son_type (Node* node) {

    assert (node);
    assert (node->parent);


    if (node == node->parent->left) return LEFT_SON;


    return RIGHT_SON;
}


int splay (Node* node) {

    assert (node);


    if (!node->parent) return 0; // root


    if (!node->parent->parent) return rotate_root (node);


    if (get_son_type (node) == get_son_type (node->parent)) {

        zig_zig (node);


        return splay (node);
    }


    zig_zag (node);


    return splay (node);
}

/*
int rotate_root (Node** node_ptr) { // parent == root

    assert (node_ptr);
    assert (cur_node);
    assert (cur_node->parent);


    SON_TYPE son_type = get_son_type (cur_node);


    Node* old_parent = cur_node->parent;printf ("cur node = %p, old parent = %p\n", cur_node, old_parent);
    cur_node->parent = nullptr;printf ("cur node = %p\n", cur_node);

    if (son_type == LEFT_SON) {

        old_parent->left = cur_node->right;
        cur_node->right  = old_parent;


        return 0;
    }


    old_parent->right = cur_node->left; printf ("cur node = %p\n", cur_node);
    cur_node->left    = old_parent;


    return 0;
}*/

int rotate_root (Node* node) { // parent == root

    assert (node);
    assert (node->parent);


    Node*    parent   = node->parent;
    SON_TYPE son_type = get_son_type (node);


    if (son_type == LEFT_SON) {

        small_right_rotate (parent);


        return 0;
    }


    small_left_rotate (parent);


    return 0;
}


int zig_zig (Node* node) {

    assert (node);
    assert (node->parent);
    assert (node->parent->parent);


    SON_TYPE son_type = get_son_type (node);
    Node* grandparent = node->parent->parent;
    Node*      parent = node->parent;

    if (son_type == LEFT_SON) {


        small_right_rotate (grandparent);
        small_right_rotate (parent);


        return 0;
    }


    small_left_rotate (grandparent);
    small_left_rotate (parent);


    return 0;
}


int zig_zag (Node* node) {

    assert (node);
    assert (node->parent);
    assert (node->parent->parent);


    SON_TYPE son_type = get_son_type (node);
    Node* grandparent = node->parent->parent;
    Node*      parent = node->parent;

    if (son_type == LEFT_SON) {


        small_right_rotate (parent);
        small_left_rotate  (grandparent);


        return 0;
    }


    small_left_rotate  (parent);
    small_right_rotate (grandparent);


    return 0;
}


int small_left_rotate (Node* node) { // мы уходим с вершины налево

    assert (node);


    Node*    old_parent = node->parent;
    SON_TYPE son_type   = LEFT_SON; if (old_parent) son_type = get_son_type (node);
    Node*    old_right  = node->right;


    node->parent = old_right;
    node->right  = old_right->left;
    if (old_right->left) old_right->left->parent = node;


    old_right->parent = old_parent;
    old_right->left   = node;


    if (old_parent && son_type == LEFT_SON)  old_parent->left  = old_right;
    if (old_parent && son_type == RIGHT_SON) old_parent->right = old_right;


    return 0;
}


int small_right_rotate (Node* node) {

    assert (node);


    SON_TYPE son_type = LEFT_SON; if (node->parent) son_type = get_son_type (node);
    Node* old_parent  = node->parent;
    Node* old_left    = node->left;


    node->parent = old_left;
    node->left   = old_left->right;
    if (old_left->right) old_left->right->parent = node;


    old_left->parent = old_parent;
    old_left->right  = node;


    if (old_parent && son_type == LEFT_SON)  old_parent->left  = old_left;
    if (old_parent && son_type == RIGHT_SON) old_parent->right = old_left;


    return 0;
}


char* splay_find (Splay* tree, char* key) {

    assert (tree);


    return node_find (tree->root, key);
}


char* node_find (Node* node, char* key) {

    if (!node) { printf ("can't find %s\n", key); return nullptr; }


    if (!strcmp (node->key, key)) return node->value;


    if (strcmp (node->key, key) < 0) return node_find (node->right, key);


    return node_find (node->left, key);
}


int splay_print (Splay* tree) {

    assert (tree);


    printf ("\nsplay:\n");


    return node_print (tree->root, 0);
}


int node_print (Node* node, size_t depth) {

    if (!node) return 0;


    node_print (node->left, depth + 1);


    print_tabs (depth);
    //printf ("key = %s, value = %s\n", node->key, node->value);
    printf ("par = %s key = %s left = %s right = %s\n", get_key (node->parent), node->key, get_key (node->left), get_key (node->right));


    node_print (node->right, depth + 1);


    return 0;
}


int print_tabs (size_t depth) {

    for (size_t i = 0; i < depth; i++) {

        printf ("    ");
    }


    return 0;
}


const char* get_key (Node* node) {

    if (!node) return "NULL";


    return node->key;
}


