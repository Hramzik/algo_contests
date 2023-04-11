

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

        scanf ("\n%d %d", &info.value, &info.priority);

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


    return node_push (&tree->root, info);
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


int node_push (Node** node_ptr, Node_info* info) { // node_ptr - указатель на поддерево, после выполнения функции в нем есть value, возможны повороты

    assert (node_ptr);
    assert (cur_node);
    assert (info);

    if (cur_node->value    == info->value)    return 1; // duplicate
    if (cur_node->priority == info->priority) return 1; // duplicate

    assert (info->value    > cur_node->value);
    assert (info->priority < cur_node->priority);



    if (!cur_node->right) return create_node (&cur_node->right, info);


    if (info->priority < cur_node->right->priority)  {

        return node_push (&cur_node->right, info);
    }

    // перевешиваем правое поддерево

    Node* old_right = cur_node->right;

    assert (info->value    > old_right->value);
    assert (info->priority > old_right->priority);


    create_node (&cur_node->right, info);
    cur_node->right->left = old_right;


    return 0;
}


int create_node (Node** node_ptr, Node_info* info) {

    assert (node_ptr);
    assert (info);


    cur_node = (Node*) calloc (1, NODE_SIZE);


    cur_node->value     = info->value;
    cur_node->priority = info->priority;

    cur_node->left  = nullptr;
    cur_node->right = nullptr;


    return 0;
}


int treap_print (Treap* tree) {

    assert (tree);


    printf ("0 ");


    return node_print (tree->root);
}


int node_print (Node* node) {

    assert (node);


    // printf ("%zd %zd val = %zd, pr = %zd\n", get_value (node->left), get_value (node->right), node->value, node->priority);
    printf ("%d %d\n", get_value (node->left), get_value (node->right)); // finish describing myself


    if (node->left) {

        printf ("%d ", node->value); // start describing left son
        node_print (node->left);
    }

    if (node->right) {

        printf ("%d ", node->value); // start describing left son
        node_print (node->right);
    }


    return 0;
}


int get_value (Node* node) {

    if (!node) return 0;


    return node->value;
}


int get_priority (Node* node) {

    if (!node) return 0;


    return node->priority;
}

