// Helper function: returns height if balanced, or -1 if unbalanced
int checkHeight(Node* node) {// give me node
    if (node == NULL) return 0;//if empty so zero balance difference

    // 1. Check Left Subtree
    int leftH = checkHeight(node->left);
    if (leftH == -1) return -1; // If left is unbalanced, pass the error up

    // 2. Check Right Subtree
    int rightH = checkHeight(node->right);
    if (rightH == -1) return -1; // If right is unbalanced, pass the error up

    // 3. Check Current Node Balance
    if (abs(leftH - rightH) > 1) return -1;

    // 4. Return actual height if everything is fine
    return 1 + max(leftH, rightH);
}

bool isAVL(Node* root) {
    // If checkHeight returns anything other than -1, it's valid
    return checkHeight(root) != -1;// if height difference is more than -1 return -1 than return 0 false isAVL()
}