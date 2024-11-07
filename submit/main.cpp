/*
* Dummy file입니다.
* 본인이 테스트하고 싶은 내용으로 변경 후 사용하세요.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
using namespace std;


class Node{
    public:
        int key;
        int height;
        string op;
        Node* left;
        Node* right;
        Node() : key(0), height(0), left(nullptr), right(nullptr) {}
};


class BSTtree{
public:
    Node* root;

    BSTtree() : root(nullptr) {}
    ~BSTtree(){clear(root);} // 메모리 누수를 막기위해 소멸자가 필요하다.

    
    
    void clear(Node* T) {
        if (!T) return;
        clear((*T).left);
        clear((*T).right);
        delete T;
    }


    void print(Node* T) {
        if (!T) return;
        cout << '<';
        print(T->left);
        cout << ' '<< T->key << ' ';
        print(T->right);
        cout << '>';
    }

    int size(Node* T){
        if (T == 0){return 0;}
        return 1 + size((*T).left) + size((*T).right);

    }

    int height(Node* T){
        if (T == nullptr){ // T가 null 일때 반환해서 작동이 안되었었다.
            return -1;
        }
        return (*T).height;
    }

    Node* minNode(Node* T){
        if (T == nullptr) return nullptr;
        if (!T->left) return T;
        return minNode(T->left);
    }

    Node* maxNode(Node* T){
        if (T == nullptr) return nullptr;
        if (!T->right) return T;
        return maxNode(T->right);
    }

    Node* getBSTNode() {
        Node* newnode = new Node();
        (*newnode).left = nullptr;
        (*newnode).right = nullptr;
        (*newnode).height = 0;
        return newnode;
    }


    void insertBST(Node*& T,int newKey){ // *& 완전한 노드를 가져오기 위해 포인터 레퍼런스 사용
        Node* p = T;
        Node* q = NULL;
        stack<Node*>stack;

         // find position to insert newKey while storing parent node on stack
        while(p != nullptr){
            if (newKey == (*p).key){ // pCar->speed = 120; // (*pCar).speed = 120;
                cout << "i "<< newKey <<": The key already exists" << endl;
                return;
            }
            q = p;
            stack.push(q);

            if (newKey < (*p).key) p = (*p).left;
            else p = (*p).right;            
        }

        // create new node
        Node* newNode = getBSTNode();
        (*newNode).key = newKey;

        // insert newNode as a child of q

        if (T == nullptr){
            T = newNode;
        }else if (newKey < (*q).key){
            (*q).left = newNode;
        }else{
            (*q).right = newNode;
        }

         // update height while popping parent node from stack
        while (stack.empty() == 0){
            q = stack.top();
            stack.pop();
            (*q).height = 1 + max(height((*q).left),height((*q).right));
        }

    }

    void deleteBST(Node*& T,int deleteKey){
        Node* p = T;
        Node* q = NULL;
        stack<Node*>stack;

        // find position of deleteKey while storing parent node on stack
        while((p != nullptr) && (deleteKey != p->key)){
            q = p;
            stack.push(q);

            if (deleteKey < (*p).key){
                p = (*p).left;
            } else {p = (*p).right;}            
        }

         if (p == nullptr) {
            cout << "d "<< deleteKey <<": The key does not exists" << endl;
            return;  // deleteKey was not found
         }


        if ((p->left != nullptr) &&( p->right != nullptr)){ // case of degree 2 is reduced
            stack.push(p);
            Node* tempNode = p;
            
            if ((size((*p).left) )<=( size((*p).right))){ // 조건이 left가 아니라 right로 적혀있었음
                p = p->right;
                while(p->left != nullptr){
                    stack.push(p);
                    p = p->left;
                }
            } else {
                p = p->left;
                while (p->right != nullptr)
                {
                    stack.push(p);
                    p = p->right;
                }
            }

            tempNode->key = p->key;

            q = stack.top(); // 유의할 것 pop 아닐 수도 있음
            stack.pop();
        
        }   // now degree of p is 0 or 1
            // delete p from T

            if((p->left == nullptr) &&( p->right == nullptr)){ // case of degree 0
                if (q == nullptr){
                    T = nullptr; // case of root
                } else if (q->left == p) { // 대입연산자로 되어있었음
                    q->left = nullptr;
                } else {q->right = nullptr;}
            } else { // case of degree 1
                if (p->left != nullptr){
                    if (q == nullptr){
                        T = T->left; // case of root

                    }else if (q->left == p){ // 비교가 아닌 대입을 넣어놓았었다.
                        q->left = p->left;
                    } else {
                        q->right = p->left; // p->left가 right 이였음
                    }
                } else {
                    if (q == nullptr) { // case of root
                        T = T->right;
                    }else if (q->left == p){
                        q->left = p->right;
                    }else {
                        q->right = p->right;
                    }
                }
            }

            delete p;
            
// update height while popping parent node from stack

            while (!stack.empty()){
                q = stack.top();
                stack.pop();
                q->height = 1 + max(height((*q).left),height((*q).right));
            } 
        }
    
};



int main() 
{
    /*
    string f = "BST-input.txt"; 
    ifstream file(f); 

    // 파일 열기 
    if (!file.is_open()) {
        cerr << "파일오류" << endl;
    }
    */

    string line;
    int key;
    BSTtree tree;

    while (getline(cin, line)) { //string이 안될경우 file을 cin으로 변경
        string op = line.substr(0,1);
        key = stoi(line.substr(2));

        if (op == "i"){
            tree.insertBST(tree.root,key);
        }
        else if( op == "d"){
            tree.deleteBST(tree.root,key);
        }

        tree.print(tree.root);
        cout << endl;
    }

    // 파일 닫기
    //file.close();

    //cout << tree.minNode(tree.root)->key << endl;
    //cout << tree.maxNode(tree.root)->key << endl;

    return 0;
}




