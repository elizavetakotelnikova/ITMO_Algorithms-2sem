#include <iostream>
#include <cmath>
#include <vector>

int H(int x, int size) {
    return x % size;
}

struct Node {
    struct Node *left = nullptr, *right = nullptr;
    double key;
    int isu;
    int height = 0;
    int balance = 0;
};

struct Binary_Tree {
    struct Node *root;
    int height;
};

int find_height(Node *root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        root->height = std::max(find_height(root->left), find_height(root->right)) + 1;
    }
    return root->height;
}

void fixheight (Node *p)
{   int hl = 0;
    int hr = 0;
    if (p->left != nullptr) {
        hl = p->left->height;
    }
    if (p->right != nullptr) {
        hr = p->right->height;
    }
    p->height = std::max(hl,hr) + 1;
}

int find_balance(Node *root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        if (root->right == nullptr && root->left == nullptr) {
            root->balance = 0;
        }
        else if (root->left == nullptr) {
            root->balance = root->right->height;
        }
        else if (root->right == nullptr) {
            root->balance = 0 - root->left->height;
        }
        else {
            root->balance = root->right->height - root->left->height;
        }
    }
    find_balance(root->left);
    find_balance(root->right);
    return root->balance;
}

Node* small_rotate_left(Node *a) {
    Node *b = a->right;
    a->right = b->left;
    b->left = a;
    fixheight(a);
    fixheight(b);
    return b;
}

Node* small_rotate_right(Node *a) {
    Node *b = a->left;
    a->left = b->right;
    b->right = a;
    fixheight(a);
    fixheight(b);
    return b;
}

Node* bigRotateLeft(Node *a) {
    a->right = small_rotate_right(a->right);
    a = small_rotate_left(a);
    return a;
}

Node* bigRotateRight(Node *a) {
    a->left = small_rotate_left(a->left);
    a = small_rotate_right(a);
    return a;
}

int find_balance_one(Node *p) {
    if (p->right == nullptr && p->left == nullptr) {
        return 0;
    }
    else if (p->left == nullptr) {
        return p->right->height;
    }
    else if (p->right == nullptr) {
        return (0 - p->left->height);
    }
    else {
        return (p->right->height - p->left->height);
    }
}

Node* fix_balance(Node* p) {
    fixheight(p);
    p->balance = find_balance_one(p);
    if (p->balance == 2) {
        if (find_balance_one(p->right) < 0) {
            return(bigRotateLeft(p));
        }
        else {
            return(small_rotate_left(p));
        }
    }
    if (p->balance == -2) {
        if (find_balance_one(p->left) > 0) {
            return (bigRotateRight(p));
        }
        else {
            return(small_rotate_right(p));
        }
    }
    return p;
}

Node* insert(Node *node_tr, double value, int isu){
    if (node_tr == nullptr) {
        node_tr = new Node;
        node_tr->key = value;
        node_tr->isu = isu;
        node_tr->left = nullptr;
        node_tr->right = nullptr;
        node_tr->balance = 0;
        node_tr->height = 1;
        return node_tr;
    }
    if (isu < node_tr->isu) {
        node_tr->left = insert(node_tr->left, value, isu);
    }
    else {
        node_tr->right = insert(node_tr->right, value, isu);
    }
    return fix_balance(node_tr);
};

Node *maximum(Node *node_tr){
    if (node_tr->right == nullptr){
        return node_tr;
    }
    return maximum(node_tr->right);
}

Node* delete_node(Node *node_tr, int z) {
    if (node_tr == nullptr){
        return node_tr;
    }
    if (z < node_tr->isu) {
        node_tr->left = delete_node(node_tr->left, z);
    }
    else if (z > node_tr->isu) {
        node_tr->right = delete_node(node_tr->right, z);
    }
    else if ((node_tr->left != nullptr) && (node_tr->right != nullptr)){
        Node* node_left = maximum(node_tr->left);
        node_tr->isu = node_left->isu;
        node_tr->key = node_left->key;
        node_tr->left = delete_node(node_tr->left, node_tr->isu);
    }
    else {
        if (node_tr->left != nullptr) {
            node_tr = node_tr->left;
        }
        else if (node_tr->right != nullptr) {
            node_tr = node_tr->right;
        }
        else {
            node_tr = nullptr;
        }
    }
    if (node_tr == nullptr) {
        return node_tr;
    }
    return fix_balance(node_tr);
};

void Inorder_traversal(Node* node, int &sum, int &count) {
    if (node != nullptr) {
        Inorder_traversal(node->left, sum, count);
        Inorder_traversal(node->right, sum, count);
        sum += node->key;
        count++;
    }
}

void Inorder_traversal_search(Node* node, double &max) {
    if (node != nullptr) {
        Inorder_traversal_search(node->left, max);
        Inorder_traversal_search(node->right, max);
        if (node->key > max) {
            max = node->key;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    int N, Q, group_isu, student_isu, points, h;
    unsigned char req;
    std::cin >> N >> Q;
    std::vector<std::pair<Node*, int>> group_table;
    //Node* group_table[N + 1];
    N = 2*N;
    group_table.resize(N + 1);
    for (int i = 0; i < N + 1; i++) {
        group_table[i].first = nullptr;
        group_table[i].second = -1;
    }
    for (int k = 0; k < Q; k++) {
        std::cin >> req;
        if (req == '+') {
            std::cin >> group_isu >> student_isu >> points;
            h = H(group_isu, N);
            while (group_table[h].second != -1) {
                if (group_table[h].second == group_isu) {
                    break;
                }
                h++;;
            }
            group_table[h].second = group_isu;
            if (group_table[h].first == nullptr) {
                group_table[h].first = new Node;
                group_table[h].first->key = points;
                group_table[h].first->isu = student_isu;
            }
            else {
                group_table[h].first = insert(group_table[h].first, points, student_isu);
            }
        }
        if (req == '-') {
            std::cin >> group_isu >> student_isu;
           h = H(group_isu, N);
            while (group_table[h].second != -1) {
                if (group_table[h].second == group_isu) {
                    break;
                }
                h++;
            }
            group_table[h].first = delete_node(group_table[h].first, student_isu);
        }
        if (req == 'm') {
            std::cin >> group_isu;
            h = H(group_isu, N);
            double max = 0;
            while (group_table[h].second != -1) {
                if (group_table[h].second == group_isu) {
                    break;
                }
                h++;
            }
            Inorder_traversal_search(group_table[h].first, max);
            std::cout << max << "\n";
        }
        if (req == 'a') {
            std::cin >> group_isu;
            h = H(group_isu, N);
            int sum = 0;
            int del = 0;
            while (group_table[h].second != -1) {
                if (group_table[h].second == group_isu) {
                    break;
                }
                h++;
            }
            Inorder_traversal(group_table[h].first, sum, del);
            if (del == 0) {
                std::cout << 0 << "\n";
            }
            else {
                std::cout << sum / del << "\n";
            }
        }
    }
    return 0;
}
