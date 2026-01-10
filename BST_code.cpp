#include <iostream>
using namespace std;
class Node {
    public:
        int info;
        Node* right;
        Node* left;
        Node(int val) {
            info = val;
            right = left = nullptr;
        }
};
class BST {
    public:
        Node* root;
        BST() {
            root = nullptr;
        }
        ~BST() {
			deleteTree(root);
        }
        void preOrder() {
            preOrder(root);
            cout << endl;
		}
        void preOrder(Node* n) {
            if (n == nullptr) {
                return;
            }
            cout << n->info << "\t";
            preOrder(n->left);
            preOrder(n->right);
        }
        void inOrder() {
            inOrder(root);
            cout << endl;
		}
        void inOrder(Node* n) {
            if (n == nullptr) {
                return;
            }
            inOrder(n->left);
            cout << n->info << "\t";
            inOrder(n->right);
        }
        void postOrder() {
            postOrder(root);
            cout << endl;
        }
        void postOrder(Node* n) {
            if (n == nullptr) {
                return;
            }
            postOrder(n->left);
            postOrder(n->right);
            cout << n->info << "\t";
        }
        Node* parent(Node* curr, Node* p, Node* par) {
            if (curr == nullptr) {
                return nullptr;
            }
            if (curr == p) {
                return par;
            }
            else {
                Node* t = nullptr;
                t = parent(curr->left, p, curr);
                if (t != nullptr) {
                    return t;
                }
                return (parent(curr->right, p, curr));
            }
        }
        Node* sibling(Node* root, Node* p) {
            Node* par = parent(root, p, nullptr);
            if (par == nullptr) return nullptr;
            if (par->left == p) {
                return par->right;
            }
            return par->left;
        }
        int getLevel(Node* ptr,int val,int level) {
            if (ptr == nullptr) {
                return -1;
            }
            if (ptr->info == val) {
                return level;
            }/*
			int downlevel = getLevel(ptr->left, val, level + 1);
            if (downlevel != -1) {
                return downlevel;
            }
            downlevel = getLevel(ptr->right, val, level + 1);
			return downlevel;
		}*/
            int left = getLevel(ptr->left, val, level + 1);
            int right = getLevel(ptr->right, val, level + 1);
            if (left > right) {
                return left;
            }
            return right;
		}
        bool find(Node* ptr, int val) {
            if (ptr == nullptr) {
                return 0;
            }
            if (ptr->info == val) {
                return 1;
            }
            bool left = find(ptr->left, val);
            bool right = find(ptr->right, val);
            return (left || right);
        }
        int maxDepth(Node* node) {
            if (node == nullptr) {
                return -1;
            }
            else {
                int lDepth = maxDepth(node->left);
                int rDepth = maxDepth(node->right);
                // return max(lDepth,rDepth)+1; 
                if (lDepth > rDepth) {
                    return (lDepth + 1);
                }
                else {
                    return (rDepth + 1);
                }
            }
		}
        void deleteTree(Node* leaf) {
            if (leaf == nullptr) {
                return;
            }
            deleteTree(leaf->left);
            deleteTree(leaf->right);
            delete leaf;
		}
        void deleteTree() {
            deleteTree(root);
			root = nullptr;
        }
        bool isEmpty() {
            return (root == nullptr);
		}
        bool isLeaf(Node* n) {
            return (n->left == nullptr && n->right == nullptr);
        }
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
        /*bool Search(Node* n, int val) {
            if (n == nullptr) {
                return false;
            }
            if (n->info == val) {
                return true;
            }
            if (val < n->info) {
                return Search(n->left, val);
            }
            else {
                return Search(n->right, val);
            }
		}*/
        Node* Search(Node* n, int val) {
            if (n == nullptr || n->info == val) {
                return n;
            }
            if (val < n->info) {
                return Search(n->left, val);
            }
            else {
                return Search(n->right, val);
            }
        }
		// Memorise All Notes to the Point That You No longer Need Them Anymore
        // AL-Ghazali
        Node* insert(Node* n, int val) {
            if (n == nullptr) {
                return new Node(val);
            }
            if(n->info == val) {
                return n; // No Duplicates Allowed
			}
			else if (val < n->info) {
                n->left = insert(n->left, val);
            }
            else {
                n->right = insert(n->right, val);
            }
			return n;
        }
        void insert(int val) {
            root = insert(root, val);
        }
        void deleteNode(int val) {
            Node* p = Search(root, val);
            if (p != nullptr) {
                deleteNode(p);
            }
		}
        void deleteNode(Node* p) {
			Node* par = parent(root, p, nullptr);
            if (isLeaf(p)) {
                if (p == root) {
                    root = nullptr;
                }
                else if (par->left == p) {
                    par->left = nullptr;
                }
                else {
                    par->right = nullptr;
                }
                delete p;
            }
            else if (p->left != nullptr && p->right != nullptr) {
                Node* succ = p->right;
                Node* succPar = p;

                while (succ->left != nullptr) {
                    succPar = succ;
                    succ = succ->left;
                }
                if (succPar != p) {
                    succPar->left = succ->right;
                }
                else {
                    succPar->right = succ->right;
                }
				succ->left = p->left;
                if (succ != p->right) {  // Important: avoid self-reference
                    succ->right = p->right;
                }
                if (par == nullptr) {
                    root = succ;
				}
                else if (par->left == p) {
                    par->left = succ;
                }
                else {
                    par->right = succ;
                }
                delete p;
                /*int val = succ->info;
                deleteNode(succ);
                p->info = val;*/
            }
            else {
                Node* child = (p->left != nullptr) ? p->left : p->right;
                if (p == root) {
					root = child;
                }
                else if (par->left == p) {
                    par->left = child;
                }
                else {
                    par->right = child;
                }
                delete p;

			}
		}
};
int main()
{

    BST tree;

    // Test the tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inorder traversal: ";
    tree.inOrder();

    cout << "Preorder traversal: ";
    tree.preOrder();

    cout << "Postorder traversal: ";
    tree.postOrder();

    cout << "Search 40: " << ((tree.Search(tree.root, 40)!=nullptr) ? "Found" : "Not found") << endl;
    cout << "Search 100: " << ((tree.Search(tree.root, 100)!=nullptr) ? "Found" : "Not found") << endl;

    //cout << "Level of 40: " << tree.getLevel(tree.root, 40, 0) << endl;
    //cout << "Max depth: " << tree.maxDepth(tree.root) << endl;

    cout << "\nDeleting 20 (leaf): ";
    tree.deleteNode(20);
    tree.inOrder();

    cout << "Deleting 30 (one child): ";
    tree.deleteNode(30);
    tree.inOrder();

    cout << "Deleting 50 (two children): ";
    tree.deleteNode(50);
    tree.inOrder();

    return 0;
}