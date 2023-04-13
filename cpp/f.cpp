

#include "../hpp/f.hpp"


//--------------------------------------------------


int main (void) {

    srand ((unsigned int) time (nullptr));


    treap_solve ();


    return 0;
}


int treap_solve (void) {

    Treap* tree = treap_ctor ();


    size_t       n              = 0; assert (scanf ("%zd", &n));
    char         cmd [20]       = "";
    Command_code prev_operation = CC_INSERT;
    int          prev_result    = 0;

    int  arg1   = 0;
    int  arg2   = 0;
    int  status = 0;

    for (size_t i = 0; i < n; i++) {

        if (scanf ("%s %d", cmd, &arg1) == -1) break;


        switch (get_command_code (cmd)) {

            case CC_INSERT: {

                if (prev_operation == CC_SUM) arg1 = (arg1 + prev_result) % 1000000000;
                Node_info info = { arg1, rand () };
                treap_push (tree, info);
                prev_operation = CC_INSERT;
                break;
            }

            case CC_SUM: {

                scanf ("%d", &arg2);
                prev_result = treap_sum_lr (tree, arg1, arg2);
                printf ("%d\n", prev_result);
                prev_operation = CC_SUM;
                break;
            }

            case CC_UNKNOWN: printf ("wrong cmd"); return 1;
            default:         return 1; // never happens
        }


        treap_print (tree);


        if (status) { printf ("ERROR\n"); return 0; }
    }


    treap_dtor (tree);


    return 0;
}


Command_code get_command_code (char* cmd) {

    if (!cmd) return CC_UNKNOWN;


    if (!strcmp (cmd, "+")) return CC_INSERT;
    if (!strcmp (cmd, "?")) return CC_SUM;


    return CC_UNKNOWN;
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


int node_repair_subtree_sum (Node* node) {

    if (!node) return 0;


    node->subtree_sum = get_subtree_sum (node->left) + get_subtree_sum (node->right) + node->key;


    return 0;
}


int get_subtree_sum (Node* node) {

    if (!node) return 0;


    return node->subtree_sum;
}


Node_pair treap_split (Treap* tree, int key) {

    assert (tree);


    return node_split (tree->root, key);
}


Node_pair node_split (Node* node, int key) {

    if (!node) { Node_pair ans = { nullptr, nullptr }; return ans; }


    if (node->key == key) { Node_pair ans = { node->left, node->right }; return ans; }
                                     // типа этого ключа тут нет, разбиваем на поддеревья со СТРОГИМИ условиями на ключи
                                     // тогда добавление существующего ключа будет работать корректно


    if (key > node->key) return node_split_big_key (node, key);


    return node_split_small_key (node, key);
}


Node_pair node_split_big_key (Node* node, int key) {

    assert (node);
    assert (key > node->key);


    Node* new_left_root  = node; // справа еще подвесим другую хню
    Node* new_right_root = nullptr;


    Node_pair right_subtrees = node_split (node->right, key);


    new_left_root->right = right_subtrees.left;  // left,  размер некорректный
    new_right_root       = right_subtrees.right; // right, размер   корректный


    node_repair_subtree_sum (new_left_root);


    Node_pair ans = { new_left_root, new_right_root };
    return ans;
}


Node_pair node_split_small_key (Node* node, int key) {

    assert (node);
    assert (key < node->key);


    Node* new_left_root  = nullptr;
    Node* new_right_root = node; // слева еще подвесим другую хню


    Node_pair left_subtrees = node_split (node->left, key);


    new_left_root        = left_subtrees.left;  // left,  размер корректный
    new_right_root->left = left_subtrees.right; // right, размер некорректный


    node_repair_subtree_sum (new_right_root);


    Node_pair ans = { new_left_root, new_right_root };
    return ans;
}


Node* node_merge (Node_pair pair) {

    // в левом поддереве ключи строго меньше, чем в правом

    if (!pair.left)  return pair.right;
    if (!pair.right) return pair.left;


    if (pair.left->priority > pair.right->priority) return node_merge_top_left  (pair);


    return node_merge_top_right (pair);
}


Node* node_merge_top_left (Node_pair pair) {

    assert (pair.left->priority > pair.right->priority);


    Node* result = pair.left; // top, левое поддерево уже корректное


    Node_pair merge_arg = { pair.left->right, pair.right };
    result->right = node_merge (merge_arg);


    node_repair_subtree_sum (result); // чиним размер


    return result;
}


Node* node_merge_top_right (Node_pair pair) {

    assert (pair.left->priority < pair.right->priority);


    Node* result = pair.right; // top, правое поддерево уже корректное


    Node_pair merge_arg = { pair.left, pair.right->left };
    result->left = node_merge (merge_arg);


    node_repair_subtree_sum (result); // чиним размер


    return result;
}


int treap_push (Treap* tree, Node_info info) {

    assert (tree);


    Node* new_node = create_node (info);


    Node_pair splited_subtrees = treap_split (tree, info.key);


    Node_pair merge1_arg = { splited_subtrees.left, new_node };
    tree->root = node_merge (merge1_arg);

    Node_pair merge2_arg = { tree->root, splited_subtrees.right };
    tree->root = node_merge (merge2_arg);


    return 0;
}


Node* create_node (Node_info info) {

    Node* node = (Node*) calloc (1, NODE_SIZE);


    node->key      = info.key;
    node->priority = info.priority;

    node->subtree_sum = info.key; // дерево из одного элемента

    node->left  = nullptr;
    node->right = nullptr;


    return node;
}


int treap_print (Treap* tree) {

    assert (tree);


    printf ("0 ");


    return node_print (tree->root);
}


int node_print (Node* node) {

    assert (node);


    printf ("%d %d val = %d, pr = %d, sum = %d\n", get_value (node->left), get_value (node->right), node->key, node->priority, node->subtree_sum);
    // printf ("%d %d\n", get_value (node->left), get_value (node->right)); // finish describing myself


    if (node->left) {

        printf ("%d ", node->key); // start describing left son
        node_print (node->left);
    }

    if (node->right) {

        printf ("%d ", node->key); // start describing left son
        node_print (node->right);
    }


    return 0;
}


int get_value (Node* node) {

    if (!node) return 0;


    return node->key;
}


int treap_sum_lr (Treap* tree, int l, int r) {

    assert (tree);


    bool deleted_left_border  = treap_exists (tree, l - 1);
    bool deleted_right_border = treap_exists (tree, r + 1);


    int result = node_sum_lr (&tree->root, l, r);


    if (deleted_left_border)  { Node_info info = { l - 1, rand () }; treap_push (tree, info); }
    if (deleted_right_border) { Node_info info = { r + 1, rand () }; treap_push (tree, info); }


    return result;
}


//--------------------------------------------------
#define cur_node (*node_ptr)
//--------------------------------------------------

int node_sum_lr (Node** node_ptr, int l, int r) {

    assert (node_ptr);


    if (!cur_node) return 0;


    
    Node_pair subtrees_split_1 = node_split (cur_node, l - 1); // may be overflow, but who cares
    // Node*     remainder1       = subtrees_split_1.left;


    Node_pair subtrees_split_2 = node_split (subtrees_split_1.right, r + 1); // may be overflow, but who cares
    // Node*     remainder2       = subtrees_split_1.right;


    int ans = get_subtree_sum (subtrees_split_2.left);


    subtrees_split_1.right = node_merge (subtrees_split_2); // restored right
    cur_node               = node_merge (subtrees_split_1); // restored node


    return ans;
}




bool treap_exists (Treap* tree, int key) {

    assert (tree);


    return node_exists (tree->root, key);
}


bool node_exists (Node* node, int key) {

    if (!node) return false;


    if (node->key == key) return true;


    if (node->key < key) return node_exists (node->right, key);


    return node_exists (node->left, key);
}

