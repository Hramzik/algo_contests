

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
        // treap_print (tree);
        // printf ("\n\n\n");


        if (status) { printf ("NO\n"); return 0; }
    }


    printf ("YES\n");
    treap_print (tree);


    treap_dtor  (tree);


    return 0;
}


Treap* treap_ctor (void) {

    Treap* tree = (Treap*) calloc (1, TREAP_SIZE);


    tree->root = nullptr;


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


    if (!tree->root || info->priority > tree->root->priority) return treap_push_root (tree, info);


    return node_push (tree->root, info);
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


    create_node (&tree->root, info);


    if (!old_root) return 0;


    if (old_root->value < info->value) tree->root->left  = old_root; // подвесим влево
    else                               tree->root->right = old_root; // подвесим вправо


    return 0;
}


int node_push (Node* node, Node_info* info) { // node_ptr - указатель на поддерево, после выполнения функции в нем есть value, возможны повороты

    assert (node);
    assert (info);

    if (node->value    == info->value)    return 1; // duplicate
    if (node->priority == info->priority) return 1; // duplicate

    assert (info->value    > node->value);
    assert (info->priority < node->priority);



    if (!node->right) return create_node (&node->right, info);


    if (info->priority < node->right->priority)  {

        return node_push (node->right, info);
    }

    // перевешиваем правое поддерево

    Node* old_right = node->right;

    assert (info->value    > old_right->value);
    assert (info->priority > old_right->priority);


    create_node (&node->right, info);
    node->right->left = old_right;


    return 0;
}


int create_node (Node** node_ptr, Node_info* info) {

    assert (node_ptr);
    assert (info);


    cur_node = (Node*) calloc (1, NODE_SIZE);


    cur_node->value    = info->value;
    cur_node->priority = info->priority;

    cur_node->left  = nullptr;
    cur_node->right = nullptr;


    return 0;
}


int treap_print (Treap* tree) {

    assert (tree);


    return node_print (tree->root, 0);
}


int node_print (Node* node, int parent) {

    assert (node);


    if (node->left) {

        node_print (node->left, node->value);
    }


    //printf ("%d %d %d val = %d, pr = %d\n", parent, get_value (node->left), get_value (node->right), node->value, node->priority);
    printf ("%d %d %d\n", parent, get_value (node->left), get_value (node->right)); // finish describing myself


    if (node->right) {

        node_print (node->right, node->value);
    }


    return 0;
}


int get_value (Node* node) {

    if (!node) return 0;


    return node->value;
}

