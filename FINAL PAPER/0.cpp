#include<iostream>
#include <cstdlib>
using namespace std;//globally stored in meta data of process 👍 jogar by hammad
struct Node{
    int val;
    Node* left;
    Node* right;
    Node(int v):val(v), left(nullptr), right(nullptr){} 
};
class BST{
    public:
        Node* root;
        BST():root(nullptr){}
        ~BST(){
            deleteTree(root);
        }
        void deleteTree(Node* node){
            if(node != nullptr){
                deleteTree(node->left);
                deleteTree(node->right);
                delete node;
            }
        }
        int maxDepth(Node* node){
            if(node == nullptr) {
                return -1;
            } else {
                int lDepth = maxDepth(node->left);
                int rDepth = maxDepth(node->right);
                if(lDepth > rDepth){
                    return lDepth + 1;
                } else {
                    return rDepth + 1;
                }
            }
        }
        int getlevel(Node* node, int val, int level){
            if(node == nullptr){
                return -1;
            }
            if(node->val == val){
                return level;
            }
            int left = getlevel(node->left, val, level + 1);
            if(left != -1){
                return left;
            } 
            return getlevel(node->right, val, level + 1);
        }
        Node* parent(Node* curr, Node* p, Node* par){
            if (curr==nullptr){
                return nullptr;
            }
            if(p == nullptr){
                return nullptr;
            }
            if(curr == p){
                return par;
            }
            else{
                Node* t = nullptr;
                t = parent(curr->left, p, curr);
                if(t != nullptr){
                    return t;
                }
                return parent(curr->right, p, curr);
            }
        }
        Node* sibling(Node* root, Node* p){
            Node* par = parent(root, p, nullptr);
            if(par == nullptr){
                return nullptr;
            }
            if(par->left == p){
                return par->right;
            } else {
                return par->left;
            }
        }
        void inOrder(Node* node){
            if(node != nullptr){
                inOrder(node->left);
                cout << node->val << " ";
                inOrder(node->right);
            }
        }
        void postOrder(Node* node){
            if(node != nullptr){
                postOrder(node->left);
                postOrder(node->right);
                cout << node->val << " ";
            }
        }
        void preOrder(Node* node){
            if(node != nullptr){
                cout << node->val << " ";
                preOrder(node->left);
                preOrder(node->right);
            }
        }
        Node* search(Node* n, int val){
            if (n == nullptr){
                return nullptr;
            }
            if(n->val == val){
                return n;
            }
            if(val < n->val){
                return search(n->left, val);
            } else {
                return search(n->right, val);
            }
        }
        bool searchBool(Node* n, int val){
            return (search(n, val) != nullptr);
        }
        Node* search(int val){
            return search(root, val);
        }
        int maxDepth(){
            return maxDepth(root);
        }
        int getlevel(int val){
            return getlevel(root, val, 0);
        }
        Node* parent(Node* p){
            return parent(root, p, nullptr);
        }
        Node* sibling(Node* p){
            return sibling(root, p);
        }
        void inOrder(){
            inOrder(root);
        }
        void postOrder(){
            postOrder(root);
        }
        void preOrder(){
            preOrder(root);
        }
        bool searchBool(int val){
            return searchBool(root, val);
        }
        Node* insert(Node* n, int val){
            if(n == nullptr){ 
                return new Node(val);;
            }
            if(n->val == val){
                cout << "Duplicate Value: " << val << endl;
                return n; // no duplicates
            }
            else if(val < n->val){
                n->left = insert(n->left, val);
            } else if(val > n->val){
                n->right = insert(n->right, val);
            }
            return n;
        }
        void insert(int val){
            root = insert(root, val);
        }
        Node* deleteNode(Node* n, int val){
            Node* find = search(n, val);
            Node* par = parent(find);
            if(find == nullptr){
                cout << "Value/Node not found: " << val << endl;
                return n;
            }
            if(find->left == nullptr && find->right == nullptr){//one child
                if(par == nullptr){//root
                    delete find;
                    return nullptr;
                }
                if(par->left == find){//im left of root
                    par->left = nullptr;
                }
                else {//im rigt
                    par->right = nullptr;
                }
                delete find;
            } else if(find->left != nullptr && find->right == nullptr){
                if(par == nullptr){
                    Node* temp = find->left;
                    delete find;
                    return temp;
                }
                if(par->left == find){
                    par->left = find->left;
                }
                else {
                    par->right = find->left;
                }
                delete find;
            } else if(find->left == nullptr && find->right != nullptr){
                if(par == nullptr){
                    Node* temp = find->right;
                    delete find;
                    return temp;
                }
                if(par->left == find){
                    par->left = find->right;
                } else {
                    par->right = find->right;
                }
                delete find;
            } else {
                Node* succParent = find;
                Node* succ = find->right;
                while(succ->left != nullptr){
                    succParent = succ;
                    succ = succ->left;
                }
                find->val = succ->val;
                if(succParent->left == succ){
                    succParent->left = succ->right;
                } else {
                    succParent->right = succ->right;
                }
                delete succ;
            }         
        }
        void deleteNode(int val){
        	root = deleteNode(root, val);
		}
        int getHeight(int val){
            return maxDepth((search(val)));
        }
        
        // returns pointer to successor node or nullptr
        Node* findsuccessor(Node* root, int X) {
            Node* ans = nullptr;    
            while (root) {
                if (root->val > X) { 
                    ans = root; 
                    root = root->left;
                }
                else
                    root = root->right;
            }
            return ans;
        }
		// Memorise All Notes to the Point That You No longer Need Them Anymore (~not actual cos he spoke arabic but hits hard)
        // AL-Ghazali
        bool isBinarySearchTree(Node* n, int min, int max) {
            if (n == nullptr) {
                return true;
            }
            if (n->info <= min || n->info >= max) {
                return false;
            }
            return isBinarySearchTree(n->left, min, n->info) &&
                   isBinarySearchTree(n->right, n->info, max);
		}
        Node* findpredecessor(Node* root, int X) {
            Node* ans = nullptr;
            while (root) {
                if (root->val < X) {
                    ans = root; root = root->right;
                }
                else
                    root = root->left;
                }
            return ans;
        }
        // Node* nearest(int val){
        //     Node* par = parent((search(val)));
        //     Node* successor = findsuccessor(root,val);
        //     Node* predecessor = findpredecessor(root,val);
        //     int parVal = par->val,sucVal = successor->val,preVal = predecessor->val;
        //     abs()
        // }

        // nearest neighbour/s0uccsor/predsseessor
        // match node vs nearest
};
int main() {
    cout << "Welcome To Arena of Ratings: Real-Time Matchmaking Engine"<<endl;;
    BST t3;
	t3.insert(1);
	t3.insert(2);
	t3.insert(3);
	t3.insert(4);
	t3.insert(5);
	t3.inOrder();
	t3.deleteNode(1);
	t3.inOrder();
    // Insert / Search / Delete by rating
    // inorder
    return 0;
}