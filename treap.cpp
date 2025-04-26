#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

template <typename T>
class Treap {
private:
    struct Node { 
        T key;
        int priority;
        int size;
        Node* left;
        Node* right;
        Node(const T& k) : key(k), priority(rand()) /*для рандомного определения приоритета*/, size(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    static void updateSize(Node* node) { //обновляем размер
        if (node) {
            node->size = 1 + 
                (node->left ? node->left->size : 0) + 
                (node->right ? node->right->size : 0);
        }
    }

    static void split(Node* root, const T& key, Node*& left, Node*& right) { //разделение
        if (!root) {
            left = right = nullptr;
            return;
        }
        if (root->key <= key) {
            split(root->right, key, root->right, right);
            left = root;
        } else {
            split(root->left, key, left, root->left);
            right = root;
        }
        updateSize(root);
    }

    static Node* merge(Node* left, Node* right) { //слияние
        if (!left) return right;
        if (!right) return left;
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            updateSize(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            updateSize(right);
            return right;
        }
    }

    void clear(Node* node) { //очищение
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    Treap() : root(nullptr) { // конструктор
        srand(time(0)); //делает случайные значения разными (для рандомизации приоритета)
    }

    ~Treap() { //деструктор
        clear(root);
    }

    void insert(const T& key) { //вставка
        Node* left = nullptr;
        Node* right = nullptr;
        split(root, key, left, right);
        Node* new_node = new Node(key);
        root = merge(merge(left, new_node), right);
    }

    void remove(const T& key) { //удаление
        Node* left = nullptr;
        Node* mid = nullptr;
        Node* right = nullptr;
        split(root, key, left, right);
        Node* parent = nullptr;
        Node* current = left;
        while (current && current->right) {
            parent = current;
            current = current->right;
        }
        if (current && current->key == key) {
            if (parent) {
                parent->right = current->left;
            } else {
                left = current->left;
            }
            delete current;
        }
        root = merge(left, right);
    }

    int size() const { //размер
        return root ? root->size : 0;
    }
};

int main() {
    Treap<int> int_treap; //пример с int
    cout<<"int:\n";
    int_treap.insert(5);
    int_treap.insert(5);
    int_treap.insert(3);
    cout<<"Size after insert: "<<int_treap.size()<<"\n"; 
    int_treap.remove(5);
    cout<<"Size after remove: "<<int_treap.size()<<"\n"; 
    Treap<std::string> str_treap; //пример со string
    cout<<"string:\n";
    str_treap.insert("apple");
    str_treap.insert("banana");
    str_treap.insert("apple");
    cout<<"Size after insert: "<< str_treap.size()<<"\n"; 
    str_treap.remove("apple");
    cout<<"Size after remove: "<< str_treap.size()<<"\n"; 
}