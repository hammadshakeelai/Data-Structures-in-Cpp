#include <iostream>
#include <algorithm> // for std::max
#include <cmath>     // for std::abs

using namespace std;

// 1. Simple Node Structure
struct Node {
    int data;
    Node* left;
    Node* right;
};

// 2. Helper Function: Calculate Height
// Returns 0 if node is NULL, otherwise 1 + max height of children
int height(Node* node) {
    if (node == NULL) return 0;
    return 1 + max(height(node->left), height(node->right));
}

// 3. Main Function: Check if AVL
bool isAVL(Node* node) {
    // Base Case: An empty tree is balanced
    if (node == NULL) return true;

    // Step A: Get height of left and right subtrees
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    // Step B: Check Balance Factor for CURRENT node
    // Difference must be -1, 0, or 1
    bool currentBalanced = abs(leftHeight - rightHeight) <= 1;

    // Step C: Recurse
    // Current node must be balanced AND left child must be AVL AND right child must be AVL
    return currentBalanced && isAVL(node->left) && isAVL(node->right);
}

// Driver code to test
int main() {
    // Creating a simple balanced tree:
    //      2
    //     / \
    //    1   3
    Node* root = new Node{2, NULL, NULL};
    root->left = new Node{1, NULL, NULL};
    root->right = new Node{3, NULL, NULL};
    root->right = new Node{4, NULL, NULL};
    root->right = new Node{5, NULL, NULL};

    if (isAVL(root))
        cout << "Tree is AVL" << endl;
    else
        cout << "Tree is NOT AVL" << endl;

    return 0;
}