#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BSTtree {
public:
    Node* root;

    BSTtree() : root(nullptr) {}
    ~BSTtree() { clear(root); }

    void clear(Node* T) {
        if (!T) return;
        clear(T->left);
        clear(T->right);
        delete T;
    }

    void print(Node* T) {
        if (!T) return;
        cout << '<';
        print(T->left);
        cout << ' ' << T->key << ' ';
        print(T->right);
        cout << '>';
    }

    int insertBST(Node*& T, int newKey) {
        if (T == nullptr) {
            T = new Node(newKey);
            return 0;
        }
        if (newKey < T->key) {
            return insertBST(T->left, newKey);
        } else if (newKey > T->key) {
            return insertBST(T->right, newKey);
        }
        return -1; // 중복 키
    }

    int deleteBST(Node*& T, int deleteKey) {
        if (T == nullptr) return -1;

        if (deleteKey < T->key) {
            return deleteBST(T->left, deleteKey);
        } else if (deleteKey > T->key) {
            return deleteBST(T->right, deleteKey);
        } else {
            // 삭제할 노드 발견
            if (T->left == nullptr) {
                Node* temp = T->right;
                delete T;
                T = temp;
            } else if (T->right == nullptr) {
                Node* temp = T->left;
                delete T;
                T = temp;
            } else {
                // 두 자식이 모두 있는 경우
                Node* minNode = T->right;
                while (minNode->left != nullptr) {
                    minNode = minNode->left;
                }
                T->key = minNode->key;
                deleteBST(T->right, minNode->key);
            }
            return 0;
        }
    }
};

int main() 
{
    int key;
    char op;
    BSTtree tree;

    while (true) {
        if (!(cin >> op >> key)) {
            cin.clear(); // cin 상태를 초기화
            cin.ignore(10000, '\n'); // 잘못된 입력 무시
            continue; // 다음 루프 반복
        }

        if (op == 'i') {
            if (tree.insertBST(tree.root, key) == -1) {
                cout << "i " << key << ": The key already exists" << endl;
            } else {
                tree.print(tree.root);
                cout << endl;
            }
        } else if (op == 'd') {
            if (tree.deleteBST(tree.root, key) == -1) {
                cout << "d " << key << ": The key does not exist" << endl;
            } else {
                tree.print(tree.root);
                cout << endl;
            }
        } else {
            cout << "Invalid operation." << endl;
        }
    }

    tree.clear(tree.root);
    return 0;
}
