

#include "../hpp/c.hpp"


//--------------------------------------------------


int main (void) {

    srand ((unsigned int) time (nullptr));


    treap_solve ();


    return 0;
}


int treap_solve (void) {

    Treap* tree = treap_ctor ();


    char cmd [20]     = "";
    int  arg          = 0;
    int  status       = 0;

    while (true) {

        if (scanf ("%s %d", cmd, &arg) == -1) break;


        status = apply_command (tree, get_command_code (cmd), arg);
        // treap_print (tree);


        if (status) { printf ("ERROR\n"); return 0; }
    }


    treap_dtor (tree);


    return 0;
}


int apply_command (Treap* tree, Command_code code, int argument) {

    assert (tree);


    switch (code) {

        case CC_INSERT: {

            Node_info info = { argument, rand () };
            return treap_push (tree, info);
        }

        case CC_DELETE: return treap_pop  (tree, argument);
        case CC_EXISTS: return bool_print (treap_exists (tree, argument));
        case CC_NEXT:   return find_result_print (treap_find_jae (tree, argument));
        case CC_PREV:   return find_result_print (treap_find_jbe (tree, argument));
        case CC_KTH:    return find_result_print (treap_find_kth (tree, argument));

        case CC_UNKNOWN: printf ("wrong cmd"); return 1;
        default:         return 1; // never happens
    }
}


int find_result_print (Find_result result) {

    if (!result.found) {

        printf ("none\n");
        return 0;
    }


    printf ("%d\n", result.key);


    return 0;
}


int bool_print (bool arg) {

    const char* arg_str = nullptr;

    if (arg) arg_str = "true";
    else     arg_str = "false";


    printf ("%s\n", arg_str);


    return 0;
}


Command_code get_command_code (char* cmd) {

    if (!cmd) return CC_UNKNOWN;


    if (!strcmp (cmd, "insert")) return CC_INSERT;
    if (!strcmp (cmd, "delete")) return CC_DELETE;
    if (!strcmp (cmd, "exists")) return CC_EXISTS;
    if (!strcmp (cmd, "next"))   return CC_NEXT;
    if (!strcmp (cmd, "prev"))   return CC_PREV;
    if (!strcmp (cmd, "kth"))    return CC_KTH;


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


int node_repair_subtree_size (Node* node) {

    if (!node) return 0;


    node->subtree_size = get_subtree_size (node->left) + get_subtree_size (node->right) + 1;


    return 0;
}


size_t get_subtree_size (Node* node) {

    if (!node) return 0;


    return node->subtree_size;
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


    node_repair_subtree_size (new_left_root);


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


    node_repair_subtree_size (new_right_root);


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


    node_repair_subtree_size (result); // чиним размер


    return result;
}


Node* node_merge_top_right (Node_pair pair) {

    assert (pair.left->priority < pair.right->priority);


    Node* result = pair.right; // top, правое поддерево уже корректное


    Node_pair merge_arg = { pair.left, pair.right->left };
    result->left = node_merge (merge_arg);


    node_repair_subtree_size (result); // чиним размер


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


int treap_pop (Treap* tree, int key) {

    assert (tree);


    Node_pair splited_subtrees = treap_split (tree, key); // разделили, если ключ был, то он пропал


    tree->root = node_merge (splited_subtrees); // слили обратно уже без ключа


    return 0;
}


Node* create_node (Node_info info) {

    Node* node = (Node*) calloc (1, NODE_SIZE);


    node->key      = info.key;
    node->priority = info.priority;

    node->subtree_size = 1; // дерево из одного элемента

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


    printf ("%d %d val = %d, pr = %d, size = %zd\n", get_value (node->left), get_value (node->right), node->key, node->priority, node->subtree_size);
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


Find_result treap_find_jae (Treap* tree, int key) {

    assert (tree);


    Find_result result = node_find_jae (tree->root, key);


    return result;
}


Find_result node_find_jae (Node* node, int key) {

    if (!node) { Find_result ans = { 0, false }; return ans; }


    if (node->key == key) { Find_result ans = { key, true }; return ans; }


    if (node->key < key) return node_find_jae (node->right, key);


    //--------------------------------------------------

    Find_result left_result = node_find_jae (node->left, key);


    if (left_result.found) return left_result;


    Find_result ans = { node->key, true };
    return ans;
}


Find_result treap_find_jbe (Treap* tree, int key) {

    assert (tree);


    Find_result result = node_find_jbe (tree->root, key);


    return result;
}


Find_result node_find_jbe (Node* node, int key) {

    if (!node) { Find_result ans = { 0, false }; return ans; }


    if (node->key == key) { Find_result ans = { key, true }; return ans; }


    if (node->key > key) return node_find_jbe (node->left, key);


    //--------------------------------------------------

    Find_result right_result = node_find_jbe (node->right, key);


    if (right_result.found) return right_result;


    Find_result ans = { node->key, true };
    return ans;
}


Find_result treap_find_kth (Treap* tree, size_t k) {

    assert (tree);


    return node_find_kth (tree->root, k);
}


Find_result node_find_kth (Node* node, size_t k) {

    if (get_subtree_size (node) < k + 1) { Find_result ans = { 0, false }; return ans; }
                                                              // у нас есть только [0, s - 1];
                                                              // s - 1 >= k
                                                              // s >= k + 1


    if (get_subtree_size (node->left) == k) { Find_result ans = { node->key, true }; return ans; }
                                                              // слева [0, k-1] => я = k при индексации с нуля


    if (get_subtree_size (node->left) > k) return node_find_kth (node->left, k);


    return node_find_kth (node->right, k - (get_subtree_size (node->left) + 1)); // уже посчитали left_size + 1
}


