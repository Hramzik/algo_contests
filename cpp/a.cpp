

#include "../hpp/a.hpp"


//--------------------------------------------------


int main (void) {

    avl_solve ();


    return 0;
}


int avl_solve (void) {

    Avl* tree = avl_ctor ();


    size_t n           = 0; assert (scanf ("%zd", &n));
    char   cmd         = 0;
    char   prev_cmd    = 0;
    int    prev_result = 0;
    size_t argument    = 0;

    for (size_t i = 0; i < n; i++) {

        prev_cmd = cmd;
        scanf ("\n%c %zd", &cmd, &argument);

        switch (cmd) {

            case '+': case_plus_sr     (tree, argument, prev_cmd,  prev_result); break;
            case '?': case_question_sr (tree, argument,           &prev_result); break;

            default: printf ("wtf you entered dumbass\n"); return 0;
        }
    }


    avl_dtor (tree);


    return 0;
}


int case_plus_sr (Avl* tree, size_t argument, char prev_cmd, int prev_result) {

    assert (tree);


    if (prev_cmd == '?') {

        size_t value = (argument + prev_result) % (1'000'000'000);
        return avl_push (tree, value);
    }


    return avl_push (tree, argument);
}


int case_question_sr (Avl* tree, size_t argument, int* prev_result) {

    assert (tree);
    assert (prev_result);


    *prev_result = avl_ask (tree, argument);


    printf ("%d\n", *prev_result);


    return 0;
}


Avl* avl_ctor (void) {

    Avl* tree = (Avl*) calloc (1, AVL_SIZE);


    tree->root = nullptr;


    return tree;
}


int avl_dtor (Avl* tree) {

    assert (tree);


    node_dtor (tree->root);


    free (tree);


    return 0;
}


int node_dtor (Node* node) {

    if (!node) return 0;


    if (node->left)  node_dtor (node->left);
    if (node->right) node_dtor (node->right);


    free (node);


    return 0;
}


int avl_push (Avl* tree, size_t value) {

    assert (tree);


    return node_push (&tree->root, value);
}


//--------------------------------------------------
#define cur_node (*node_ptr)
#define height_diff (int) get_height (cur_node->left) - (int) get_height (cur_node->right)
//--------------------------------------------------

int node_push (Node** node_ptr, size_t value) { // node_ptr - указатель на поддерево, после выполнения функции в нем есть value, возможны повороты

    assert (node_ptr);


    if (!cur_node) return create_node (node_ptr, value);


    if (cur_node->value == value) return 0;


    if (cur_node->value > value)  {

        node_push     (&cur_node->left, value);
        update_height ( cur_node);

        if (height_diff == 2) rotate_right (node_ptr);


        return 0;
    }


    // cur_node->value < value

    node_push     (&cur_node->right, value);
    update_height ( cur_node);

    if (height_diff == -2) rotate_left (node_ptr);


    return 0;
}


int create_node (Node** node_ptr, size_t value) {

    assert (node_ptr);


    cur_node = (Node*) calloc (1, NODE_SIZE);


    cur_node->value  = value;
    cur_node->height = 1;

    cur_node->left  = nullptr;
    cur_node->right = nullptr;


    return 0;
}


int update_height (Node* node) {

    if (!node) return 0;


    size_t left_height  = get_height (node->left);
    size_t right_height = get_height (node->right);

    node->height = my_max (left_height, right_height) + 1;


    return 0;
}


size_t get_height (Node* node) {

    if (!node) return 0;


    return node->height;
}

size_t my_max (size_t val1, size_t val2) {

    if (val1 > val2) return val1;


    return val2;
}

int rotate_left (Node** node_ptr) {

    assert (height_diff == -2);
    assert (node_ptr);
    assert (cur_node);
    assert (cur_node->right);


    size_t right_left_height  = get_height (cur_node->right->left);
    size_t right_right_height = get_height (cur_node->right->right);

    if (right_left_height > right_right_height) small_right_rotate (&cur_node->right); // "БОЛЬШОЕ" левое вращение


    return small_left_rotate (node_ptr);
}


int small_left_rotate (Node** node_ptr) {

    assert (node_ptr);
    assert (node_ptr);
    assert (cur_node);


    Node* old_right = cur_node->right;

    cur_node->right = old_right->left;
    old_right->left = cur_node;


    update_height (cur_node);
    update_height (old_right);


    cur_node = old_right;


    return 0;
}


int small_right_rotate (Node** node_ptr) {

    assert (node_ptr);
    assert (node_ptr);
    assert (cur_node);


    Node* old_left = cur_node->left;

    cur_node->left  = old_left->right;
    old_left->right = cur_node;


    update_height (cur_node);
    update_height (old_left);


    cur_node = old_left;


    return 0;
}


int rotate_right (Node** node_ptr) {

    assert (height_diff == 2);
    assert (node_ptr);
    assert (cur_node);
    assert (cur_node->left);


    size_t left_left_height  = get_height (cur_node->left->left);
    size_t left_right_height = get_height (cur_node->left->right);

    if (left_right_height > left_left_height) small_left_rotate (&cur_node->left); // "БОЛЬШОЕ" правое вращение


    return small_right_rotate (node_ptr);
}


int avl_ask (Avl* tree, size_t value) {

    assert (tree);


    int result = node_find_jae (tree->root, value);


    return result;
}


int node_find_jae (Node* node, size_t value) {

    if (!node) return -1;


    if (node->value == value) return (int) value;


    if (node->value < value) return node_find_jae (node->right, value);

    //--------------------------------------------------

    int left_result = node_find_jae (node->left, value);


    if (left_result != -1) return left_result;


    return (int) node->value;
}


