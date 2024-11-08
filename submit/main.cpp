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

    void print(Node* T) {
        if (!T) return;
        cout << '<';
        print(T->left);
        cout << ' ' << T->key << ' ';
        print(T->right);
        cout << '>';
    }

    int height(Node* T) {
        return T ? T->height : -1;
    }

    void updateSize(Node* T) {
        if (T) T->size = 1 + (T->left ? T->left->size : 0) + (T->right ? T->right->size : 0);
    }

    Node* minNode(Node* T) {
        while (T && T->left) T = T->left;
        return T;
    }

    Node* maxNode(Node* T) {
        while (T && T->right) T = T->right;
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
        if (T == nullptr) return -1;
        Node* p = T;
        Node* q = nullptr;
        stack<Node*> stack;

        // 삭제할 노드 탐색
        while (p != nullptr && deleteKey != p->key) {
            q = p;
            stack.push(q);
            if (deleteKey < p->key) p = p->left;
            else p = p->right;
        }

        if (p == nullptr) return -1; // 삭제할 노드가 없으면 -1 반환

        // degree 2인 경우, 오른쪽 서브트리의 최소 노드로 대체
        if (p->left != nullptr && p->right != nullptr) {
            stack.push(p);
            Node* successor = maxNode(p->left); // 오른쪽 서브트리의 최소 노드
            p->key = successor->key; // 현재 노드 키를 successor의 키로 교체
            q = p;
            p = p->left;

            // successor를 찾아서 제거하기 위한 탐색
            while (p != successor) {
                q = p;
                stack.push(q);
                p = p->left;
            }
        }

        // degree 1 또는 0 처리
        Node* child = (p->left != nullptr) ? p->left : p->right;

        if (q == nullptr) { // 삭제할 노드가 루트 노드인 경우
            T = child;
        } else if (q->left == p) {
            q->left = child;
        } else {
            q->right = child;
        }

        delete p;

        // 부모 노드들의 height와 size 업데이트
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
    /*    string f = "BST-input.txt"; 
    ifstream file(f); 

    // 파일 열기 
    if (!file.is_open()) {
        cerr << "파일오류" << endl;
    }
    */

    

    //string line;
    int key;
    char op;
    BSTtree tree;

    while (cin >> op >> key) { //string이 안될경우 file을 cin으로 변경

        if (op == 'i'){
            if (tree.insertBST(tree.root, key) == -1) {
                cout << "i " << key << ": The key already exists";
            } else {
                tree.print(tree.root);
            }
        }
        else if( op == 'd'){
            if (tree.deleteBST(tree.root, key) == -1) {
                cout << "d " << key << ": The key does not exist";
            } else {
                tree.print(tree.root);
            }
        }

        cout << endl;
    }

    // 파일 닫기
    //file.close();

    //cout << tree.minNode(tree.root)->key << endl;
    //cout << tree.maxNode(tree.root)->key << endl;

    return 0;
}



