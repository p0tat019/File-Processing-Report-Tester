#include <iostream>
#include <stack>
using namespace std;

class Node {
public:
    int key;
    int height;
    int size;  // 서브트리의 크기를 저장
    Node* left;
    Node* right;
    Node() : key(0), height(0), size(1), left(nullptr), right(nullptr) {}
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
        cout << '<';
        inorder(T->left);
        cout << ' ' << T->key << ' ';
        inorder(T->right);
        cout << '>';
    }

    int height(Node* T) {
        return T ? T->height : -1;
    }

    void updateSize(Node* T) {
        if (T) T->size = 1 + (T->left ? T->left->size : 0) + (T->right ? T->right->size : 0);
    }

    int size(Node* T){
        return T->size;
    }

    Node* minNode(Node* T) {
        while (T != nullptr && T->left != nullptr) {
            T = T->left; // 왼쪽 자식으로 이동
        }
        return T;
    }

    Node* maxNode(Node* T) {
        while (T != nullptr && T->right != nullptr) {
            T = T->right; // 오른쪽 자식으로 이동
        }
        return T;
    }

    Node* getBSTNode() {
        Node* newnode = new Node();
        return newnode;
    }

    int insertBST(Node*& T, int newKey) {
        Node* p = T;
        Node* q = nullptr;
        stack<Node*> stack;

        while (p != nullptr) {
            if (newKey == p->key) return -1;
            q = p;
            stack.push(q);
            if (newKey < p->key) p = p->left;
            else p = p->right;
        }

        Node* newNode = getBSTNode();
        newNode->key = newKey;

        if (T == nullptr) {
            T = newNode;
        } else if (newKey < q->key) {
            q->left = newNode;
        } else {
            q->right = newNode;
        }

        while (!stack.empty()) {
            q = stack.top();
            stack.pop();
            q->height = 1 + max(height(q->left), height(q->right));
            updateSize(q);  // size 업데이트
        }

        return 0;
    }

    int deleteBST(Node*& T, int deleteKey) {
        if (T == nullptr) return -1; // 삭제할 노드가 없으면 -1 반환
        Node* p = T;
        Node* q = nullptr; // 부모 노드
        stack<Node*> stack;

        // 삭제할 노드 탐색
        while (p != nullptr && deleteKey != p->key) {
            q = p;
            stack.push(q);
            if (deleteKey < p->key) p = p->left;
            else p = p->right;
        }

        if (p == nullptr) return -1; // 삭제할 노드가 없으면 -1 반환

        // degree 0 
        if (p->left == nullptr && p->right == nullptr) {
            if (p == T) { // 루트 노드인 경우
                delete p;
                T = nullptr; // 루트 노드 삭제
            } else {
                if (q->left == p) {
                    q->left = nullptr;
                } else {
                    q->right = nullptr;
                }
                delete p;
            }
        }
        // degree 1
        else if (p->left == nullptr || p->right == nullptr) {
            Node* child = (p->left != nullptr) ? p->left : p->right;
            if (p == T) { // 루트 노드인 경우
                T = child; // 루트 노드가 삭제될 때
            } else {
                if (q->left == p) {
                    q->left = child;
                } else {
                    q->right = child;
                }
            }
            delete p;
        }
        // degree 2 
        else {
            Node* r = minNode(p->right); // 오른쪽 서브트리의 최소 노드
            p->key = r->key; 
            deleteBST(p->right, r->key);
        }

        // height와 size 업데이트
        while (!stack.empty()) {
            q = stack.top();
            stack.pop();
            q->height = 1 + max(height(q->left), height(q->right));
            updateSize(q);  // size 업데이트
        }

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
            cout << "Invalid input." << endl;
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
