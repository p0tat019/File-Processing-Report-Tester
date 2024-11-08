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

    void print(Node* T) {
        if (!T) return;
        cout << '<';
        print(T->left);
        cout << ' ' << T->key << ' ';
        print(T->right);
        cout << '>';
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
        Node* current = root;
        Node* parent = nullptr;

        // 삭제할 노드 탐색
        while (current != nullptr && current->key != deleteKey) {
            parent = current;
            if (deleteKey < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) return -1; // 삭제할 노드가 없음

        // 삭제할 노드가 발견됨
        if (current->left == nullptr && current->right == nullptr) { // 자식이 없는 경우
            if (current == root) {
                root = nullptr; // 루트 노드 삭제
            } else if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        } else if (current->left == nullptr || current->right == nullptr) { // 자식이 하나인 경우
            Node* child = (current->left != nullptr) ? current->left : current->right;
            if (current == root) {
                root = child; // 루트 노드가 삭제될 때
            } else if (parent->left == current) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        } else { // 자식이 두 개인 경우
            Node* successor = current->right;
            Node* successorParent = current;

            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }

            current->key = successor->key; // successor의 키로 현재 노드의 키를 교체

            // successor 노드 삭제
            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }
            current = successor; // 메모리 해제할 노드
        }

        delete current; // 노드 메모리 해제
        return 0;
    }
};

int main() 
{
    int key;
    char op;
    BSTtree tree;

    while (true) {
        if (!(cin >> op >> key)) {
            cout << "Invalid input. Please enter a valid operation and key." << endl;
            cin.clear(); // cin 상태를 초기화
            cin.ignore(10000, '\n'); // 잘못된 입력 무시
            continue; // 다음 루프 반복
        }

        if (op == 'i') {
            if (tree.insertBST(key) == -1) {
                cout << "i " << key << ": The key already exists" << endl;
            } else {
                tree.print(tree.root);
                cout << endl;
            }
        } else if (op == 'd') {
            if (tree.deleteBST(key) == -1) {
                cout << "d " << key << ": The key does not exist" << endl;
            } else {
                tree.print(tree.root);
                cout << endl;
            }
        } else {
            cout << "Invalid operation. Please use 'i' for insert or 'd' for delete." << endl;
        }
    }

    tree.clear(tree.root);
    return 0;
}
