#include<iostream>
using namespace std;
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node(int value) : val(value), left(nullptr), right(nullptr) {}
};
class BinaryTree {
public:
    Node* root;
	BinaryTree() : root(nullptr) {}
    ~BinaryTree() {
        deleteTree(root);
	}
    void preOrder(Node* node) {
        if (node == nullptr) 
            return;
        cout << node->val << "    ";
        preOrder(node->left);
        preOrder(node->right);
	}
    void inOrder(Node* node) {
        if (node == nullptr)
            return;
        inOrder(node->left);
        cout << node->val << "    ";
        inOrder(node->right);
    }
    void postOrder(Node* node) {
        if (node == nullptr)
            return;
        postOrder(node->left);
        postOrder(node->right);
        cout << node->val << "    ";
    }
    Node* parent(Node* curr, Node* child, Node* par = nullptr) {
        if (curr == nullptr)
            return nullptr;
        if (curr == child)
            return par;
        Node* leftSearch = parent(curr->left, child, curr);
        if (leftSearch != nullptr)
            return leftSearch;
        return parent(curr->right, child, curr);
	}
    Node* sibling(Node* curr, Node* child) {
        Node* par = parent(root, child, nullptr);
        if (par == nullptr)
            return nullptr;
        if (par->left == child)
            return par->right;
        return par->left;
	}
    int getLevel(Node* ptr, int val, int level) {
        if (ptr == nullptr)
            return -1;
        if (ptr->val == val)
            return level;
		//int left = getLevel(ptr->left, val, level + 1);
		//int right = getLevel(ptr->right, val, level + 1);
        int downlevel = getLevel(ptr->left, val, level + 1);// X
        if (downlevel != 0)// (left > right)
			return downlevel;// return left;
		return getLevel(ptr->right, val, level + 1);// return right;
	}
    int maxDepth(Node* node) {
        if (node == nullptr)
            return -1;
        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);
        return (leftDepth > rightDepth)? leftDepth + 1 : rightDepth + 1;
	}
    void deleteTree(Node* leaf) {
        if (leaf == nullptr)
            return;
        deleteTree(leaf->left);
        deleteTree(leaf->right);
        delete leaf;
	}
};
int main() {
        return 0;
    }