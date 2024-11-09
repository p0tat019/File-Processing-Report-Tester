#include <iostream>
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

    void inorder(Node* T) {
        if (!T) return;
        inorder(T->left);
        cout << T->key << " ";
        inorder(T->right);
    }

    int insertBST(int newKey) {
        Node* newNode = new Node(newKey);
        if (root == nullptr) {
            root = newNode;
            return 0;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (newKey < current->key) {
                current = current->left;
            } else if (newKey > current->key) {
                current = current->right;
            } else {
                delete newNode; // 중복 키이므로 메모리 해제
                return -1; // 중복 키
            }
        }

        if (newKey < parent->key) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        return 0;
    }

    int deleteBST(int deleteKey) {
        // deleteBST 구현 (이전 답변에서 제공된 코드 사용)
        // ...
        return 0; // 임시 반환값
    }
};

int main() 
{
    int key;
    char op;
    BSTtree tree;

    while (true) {
        if (!(cin >> op)) {
            cout << "Invalid input." << endl;
            cin.clear(); // cin 상태를 초기화
            cin.ignore(10000, '\n'); // 잘못된 입력 무시
            continue; // 다음 루프 반복
        }

        if (!(cin >> key)) {
            cin.clear(); // cin 상태를 초기화
            cin.ignore(10000, '\n'); // 잘못된 입력 무시
            continue; // 다음 루프 반복
        }

        if (op == 'i') {
            if (tree.insertBST(key) == -1) {
                cout << "i " << key << ": The key already exists" << endl;
            } else {
                tree.inorder(tree.root);
                cout << endl;
            }
        } else if (op == 'd') {
            if (tree.deleteBST(key) == -1) {
                cout << "d " << key << ": The key does not exist" << endl;
            } else {
                tree.inorder(tree.root);
                cout << endl;
            }
        } else {
            cout << "Invalid operation." << endl;
        }
    }

    tree.clear(tree.root);
    return 0;
}
