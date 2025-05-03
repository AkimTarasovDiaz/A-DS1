#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    int size;
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1), size(1) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int size(Node* node) {
        return node ? node->size : 0;
    }

    void update(Node* node) {
        node->height = 1 + max(height(node->left), height(node->right));
        node->size = 1 + size(node->left) + size(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        update(y); //сначала обновляем бывший корень (теперь правый потомок)
        update(x); //затем новый корень поддерева
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        update(x);
        update(y);
        return y;
    }

    Node* balance(Node* node) {
        int balanceFactor = height(node->left) - height(node->right);
        if (balanceFactor > 1) {
            if (height(node->left->left) < height(node->left->right)) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }
        if (balanceFactor < -1) {
            if (height(node->right->left) > height(node->right->right)) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, int key) {
        if (!node) return new Node(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }
        update(node);
        return balance(node);
    }
    int findKthUtil(Node* node, int k) {
        int leftSize = size(node->left);

        if (k < leftSize) {
            return findKthUtil(node->left, k);
        } else if (k == leftSize) {
            return node->key;
        } else {
            return findKthUtil(node->right, k - leftSize - 1);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    int findKth(int k) {
        if (k < 0 || k >= size(root)) {
            throw out_of_range("Invalid k value");
        }
        return findKthUtil(root, k);
    }
};

int main() {
    AVLTree tree;
    tree.insert(3); tree.insert(1); tree.insert(2);
    tree.insert(4); tree.insert(5); tree.insert(6);
    cout << "3-ья порядковая статистика: " << tree.findKth(3) << endl; // Должно быть 4
    cout << "5-ая порядковая статистика: " << tree.findKth(5) << endl; // Должно быть 6
    return 0;
}