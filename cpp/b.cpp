

#include "../hpp/b.hpp"


//--------------------------------------------------


int main (void) {

    treap_solve ();


    return 0;
}


int treap_solve (void) {

    Treap* tree = treap_ctor ();


    size_t    n      = 0; assert (scanf ("%zd", &n));
    Node_info info   = { 0, 0 };
    int       status = 0;

    for (size_t i = 0; i < n; i++) {

        scanf ("%d %d", &info.value, &info.priority);
        info.value = (int) i + 1;
        info.priority *= -1; // строим на минимуме по приоритетам

        status = treap_push (tree, &info);
        //treap_print (tree);
        //printf ("\n\n\n");


        if (status) { printf ("NO\n"); return 0; }
    }


    printf ("YES\n");
    treap_print (tree);


    treap_dtor  (tree);


    return 0;
}


Treap* treap_ctor (void) {

    Treap* tree = (Treap*) calloc (1, TREAP_SIZE);


    tree->root       = nullptr;
    tree->most_right = nullptr;


    return tree;
}


int treap_dtor (Treap* tree) {

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


int treap_push (Treap* tree, Node_info* info) {

    assert (tree);


    return node_push (tree, tree->most_right, info);
}


//--------------------------------------------------
#define cur_node (*node_ptr)
//--------------------------------------------------


int treap_push_root (Treap* tree, Node_info* info) {

    assert (tree);
    assert (info);
    // assert (!tree->root || info->priority >  tree->root->priority); // совпадать может только с пустым
    // assert (!tree->root || info->value    != tree->root->value);    // совпадать может только с пустым


    Node* old_root = tree->root;


    create_node (&tree->root, info, nullptr);


    tree->most_right = tree->root;


    if (!old_root) return 0;


    if (old_root->value < info->value) tree->root->left  = old_root; // подвесим влево
    else                               tree->root->right = old_root; // подвесим вправо


    old_root->parent = tree->root;


    return 0;
}


int node_push (Treap* tree, Node* node, Node_info* info) { // node_ptr - указатель на поддерево, после выполнения функции в нем есть value, возможны повороты

    if (!node) return treap_push_root (tree, info);


    assert (info);

    if (node->value    == info->value)    return 1; // duplicate
    if (node->priority == info->priority) return 1; // duplicate

    assert (info->value > node->value);



    //printf ("current pr = %d my pr = %d\n", node->priority, info->priority);
    if (node->priority < info->priority) return node_push (tree, node->parent, info);


    Node* old_right = node->right;


    create_node (&node->right, info, node);


    tree->most_right = node->right;


    // перевешиваем правое поддерево


    node->right->left = old_right;


    if (old_right) old_right->parent = node->right;


    return 0;
}


int create_node (Node** node_ptr, Node_info* info, Node* parent) {

    assert (node_ptr);
    assert (info);


    cur_node = (Node*) calloc (1, NODE_SIZE);


    cur_node->value    = info->value;
    cur_node->priority = info->priority;

    cur_node->left   = nullptr;
    cur_node->right  = nullptr;
    cur_node->parent = parent;


    return 0;
}


int treap_print (Treap* tree) {

    assert (tree);

    //printf ("max right = %d\n", tree->most_right->value);
    return node_print (tree->root);
}


int node_print (Node* node) {

    assert (node);


    if (node->left) {

        node_print (node->left);
    }


    // printf ("%d %d %d val = %d, pr = %d\n", get_value (node->parent), get_value (node->left), get_value (node->right), node->value, node->priority);
    printf ("%d %d %d\n", get_value (node->parent), get_value (node->left), get_value (node->right)); // finish describing myself


    if (node->right) {

        node_print (node->right);
    }


    return 0;
}


int get_value (Node* node) {

    if (!node) return 0;


    return node->value;
}

