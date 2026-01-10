#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// --- Node Structure ---
struct Node {
    int rating;
    string name;
    int hp;
    Node* left;
    Node* right;

    Node(int r, string n, int h) : rating(r), name(n), hp(h), left(nullptr), right(nullptr) {}
};

// --- Arena Class (BST Wrapper) ---
class Arena {
private:
    Node* root;

    // Helper: Insert
    Node* insert(Node* node, int r, string n, int h, bool& success) {
        if (!node) {
            success = true;
            return new Node(r, n, h);
        }
        if (r == node->rating) {
            success = false; // Duplicate
        } else if (r < node->rating) {
            node->left = insert(node->left, r, n, h, success);
        } else {
            node->right = insert(node->right, r, n, h, success);
        }
        return node;
    }

    // Helper: Find Minimum Node (for deletion successor)
    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    // Helper: Delete
    Node* remove(Node* node, int r, bool& found) {
        if (!node) {
            found = false;
            return nullptr;
        }
        if (r < node->rating) {
            node->left = remove(node->left, r, found);
        } else if (r > node->rating) {
            node->right = remove(node->right, r, found);
        } else {
            // Node found
            found = true;
            // Case 1: No child
            if (!node->left && !node->right) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            // Find successor (smallest in right subtree)
            Node* temp = findMin(node->right);
            // Copy data
            node->rating = temp->rating;
            node->name = temp->name;
            node->hp = temp->hp;
            // Delete successor
            bool dummy; // We know it exists
            node->right = remove(node->right, temp->rating, dummy);
        }
        return node;
    }

    // Helper: Search
    Node* search(Node* node, int r) {
        if (!node || node->rating == r) return node;
        if (r < node->rating) return search(node->left, r);
        return search(node->right, r);
    }

    // Helper: In-order Range
    void rangeQuery(Node* node, int L, int R, bool& empty) {
        if (!node) return;
        
        if (node->rating > L) rangeQuery(node->left, L, R, empty);
        
        if (node->rating >= L && node->rating <= R) {
            cout << node->rating << " " << node->name << " " << node->hp << "\n";
            empty = false;
        }
        
        if (node->rating < R) rangeQuery(node->right, L, R, empty);
    }

    // Helper: Height
    int getHeight(Node* node) {
        if (!node) return -1; // Empty height definition
        if (!node->left && !node->right) return 0; // Single node height
        int l = getHeight(node->left);
        int r = getHeight(node->right);
        // Correct logic based on definition: if empty is -1, leaf is 0.
        // If node has children, it's 1 + max child height.
        // Base case adjustment:
        // If child is nullptr, getHeight returns -1.
        // 1 + max(-1, -1) = 0 (Leaf). Correct.
        return 1 + max(l, r);
    }

    // Helper: Count Leaves
    int getLeaves(Node* node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return getLeaves(node->left) + getLeaves(node->right);
    }

    // Helper: Count Total Players
    int getCount(Node* node) {
        if (!node) return 0;
        return 1 + getCount(node->left) + getCount(node->right);
    }

    // Helper: Find Min/Max Rating
    int getMinRating(Node* node) {
        if (!node->left) return node->rating;
        return getMinRating(node->left);
    }
    int getMaxRating(Node* node) {
        if (!node->right) return node->rating;
        return getMaxRating(node->right);
    }

    // Helper: Rank (Count < X)
    void getRank(Node* node, int X, int& count) {
        if (!node) return;
        if (node->rating < X) {
            count++; // Count this node
            getRank(node->left, X, count); // Process left
            getRank(node->right, X, count); // Process right
            // Optimization: In BST, if node < X, all left are < X.
            // But doing full traversal is safer O(N) without size fields.
            // Better logic below for BST structure:
        } else {
            // node >= X, so right subtree is definitely >= X. Only check left.
            getRank(node->left, X, count);
        }
    }
    
    // Better O(h) Rank if we assume valid BST logic
    int countStrictlyLess(Node* node, int X) {
        if (!node) return 0;
        if (node->rating == X) {
            return getCount(node->left); 
        } else if (node->rating < X) {
            // This node is < X, and entire left subtree is < X.
            // We need 1 (this node) + size(left) + whatever is < X in right subtree.
            return 1 + getCount(node->left) + countStrictlyLess(node->right, X);
        } else {
            // node->rating > X. Nothing on right is valid. Go left.
            return countStrictlyLess(node->left, X);
        }
    }

    // Helper: Kth Smallest
    void findKth(Node* node, int& k, Node*& result) {
        if (!node || result) return;
        
        findKth(node->left, k, result);
        
        if (k > 0) {
            k--;
            if (k == 0) {
                result = node;
                return;
            }
        }
        
        findKth(node->right, k, result);
    }

    // Helper: LCA for Duel
    Node* findLCA(Node* node, int n1, int n2) {
        if (!node) return nullptr;
        if (node->rating > n1 && node->rating > n2) return findLCA(node->left, n1, n2);
        if (node->rating < n1 && node->rating < n2) return findLCA(node->right, n1, n2);
        return node;
    }

    // Helper: Distance from root to node
    int getDist(Node* node, int target, int currentDist) {
        if (!node) return -1;
        if (node->rating == target) return currentDist;
        if (target < node->rating) return getDist(node->left, target, currentDist + 1);
        return getDist(node->right, target, currentDist + 1);
    }

public:
    Arena() : root(nullptr) {}

    // 1. JOIN
    void join(int r, string n, int h) {
        bool success = false;
        root = insert(root, r, n, h, success);
        if (success) cout << "JOINED\n";
        else cout << "DUPLICATE\n";
    }

    // 2. LEAVE 
    void leave(int r) {
        bool found = false;
        root = remove(root, r, found);
        if (found) cout << "LEFT\n";
        else cout << "NOT FOUND\n";
    }

    // 3. STATUS
    void status(int r) {
        Node* res = search(root, r);
        if (res) cout << res->rating << " " << res->name << " " << res->hp << "\n";
        else cout << "NOT FOUND\n";
    }

    // 4. DAMAGE
    void damage(int r, int amt) {
        Node* res = search(root, r);
        if (res) {
            res->hp = max(0, res->hp - amt);
            cout << "DAMAGED " << res->hp << "\n";
        } else {
            cout << "NOT FOUND\n";
        }
    }

    // 5. HEAL
    void heal(int r, int amt) {
        Node* res = search(root, r);
        if (res) {
            res->hp += amt;
            cout << "HEALED " << res->hp << "\n";
        } else {
            cout << "NOT FOUND\n";
        }
    }

    // Helpers for MATCH/NEXT/PREV
    void getPredecessor(Node* node, int X, Node*& best) {
        while (node) {
            if (node->rating < X) {
                best = node; // Candidate found, try to find a larger one on right
                node = node->right;
            } else {
                node = node->left; // Too big, go left
            }
        }
    }

    void getSuccessor(Node* node, int X, Node*& best) {
        while (node) {
            if (node->rating > X) {
                best = node; // Candidate found, try to find a smaller one on left
                node = node->left;
            } else {
                node = node->right; // Too small, go right
            }
        }
    }

    // 6. MATCH
    void match(int X) {
        if (!root) { cout << "EMPTY\n"; return; }

        Node* P = nullptr;
        Node* S = nullptr;
        getPredecessor(root, X, P);
        getSuccessor(root, X, S);

        if (!P && !S) { cout << "EMPTY\n"; return; } // Should not happen if root exists
        if (P && !S) { cout << P->rating << " " << P->name << " " << P->hp << "\n"; return; }
        if (!P && S) { cout << S->rating << " " << S->name << " " << S->hp << "\n"; return; }

        // Both exist
        long long distP = abs((long long)X - P->rating);
        long long distS = abs((long long)S->rating - X);

        if (distP < distS) {
             cout << P->rating << " " << P->name << " " << P->hp << "\n";
        } else if (distS < distP) {
             cout << S->rating << " " << S->name << " " << S->hp << "\n";
        } else {
            // Tied, choose P (lower rating)
             cout << P->rating << " " << P->name << " " << P->hp << "\n";
        }
    }

    // 7. NEXT
    void next(int X) {
        Node* S = nullptr;
        getSuccessor(root, X, S);
        if (S) cout << S->rating << " " << S->name << " " << S->hp << "\n";
        else cout << "NONE\n";
    }

    // 8. PREV
    void prev(int X) {
        Node* P = nullptr;
        getPredecessor(root, X, P);
        if (P) cout << P->rating << " " << P->name << " " << P->hp << "\n";
        else cout << "NONE\n";
    }

    // 9. RANGE
    void range(int L, int R) {
        bool empty = true;
        rangeQuery(root, L, R, empty);
        if (empty) cout << "EMPTY\n";
    }

    // 10. RANK
    void rank(int X) {
        cout << countStrictlyLess(root, X) << "\n";
    }

    // 11. KTH
    void kth(int k) {
        int total = getCount(root);
        if (k < 1 || k > total) {
            cout << "OUT OF RANGE\n";
            return;
        }
        Node* res = nullptr;
        findKth(root, k, res);
        if (res) cout << res->rating << " " << res->name << " " << res->hp << "\n";
    }

    // 12. DUEL
    void duel(int A, int B) {
        if (!search(root, A) || !search(root, B)) {
            cout << "NOT FOUND\n";
            return;
        }
        Node* lca = findLCA(root, A, B);
        // Distance is dist(LCA, A) + dist(LCA, B)
        // Since getDist calculates edges from a root, we use lca as the temp root
        int d1 = getDist(lca, A, 0);
        int d2 = getDist(lca, B, 0);
        cout << "DIST " << (d1 + d2) << "\n";
    }

    // 13. STATS
    void stats() {
        int n = getCount(root);
        cout << "PLAYERS " << n << "\n";
        
        if (n == 0) {
            cout << "MIN NONE\n";
            cout << "MAX NONE\n";
        } else {
            cout << "MIN " << getMinRating(root) << "\n";
            cout << "MAX " << getMaxRating(root) << "\n";
        }
        
        cout << "HEIGHT " << getHeight(root) << "\n";
        cout << "LEAVES " << getLeaves(root) << "\n";
    }
};

int main() {
    // Fast I/O
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Arena game;
    int Q;
    if (!(cin >> Q)) return 0;

    string cmd;
    while (Q--) {
        cin >> cmd;
        if (cmd == "JOIN") {
            int r, hp; string n;
            cin >> r >> n >> hp;
            game.join(r, n, hp);
        } else if (cmd == "LEAVE") {
            int r; cin >> r;
            game.leave(r);
        } else if (cmd == "STATUS") {
            int r; cin >> r;
            game.status(r);
        } else if (cmd == "DAMAGE") {
            int r, amt; cin >> r >> amt;
            game.damage(r, amt);
        } else if (cmd == "HEAL") {
            int r, amt; cin >> r >> amt;
            game.heal(r, amt);
        } else if (cmd == "MATCH") {
            int x; cin >> x;
            game.match(x);
        } else if (cmd == "NEXT") {
            int x; cin >> x;
            game.next(x);
        } else if (cmd == "PREV") {
            int x; cin >> x;
            game.prev(x);
        } else if (cmd == "RANGE") {
            int l, r; cin >> l >> r;
            game.range(l, r);
        } else if (cmd == "RANK") {
            int x; cin >> x;
            game.rank(x);
        } else if (cmd == "KTH") {
            int k; cin >> k;
            game.kth(k);
        } else if (cmd == "DUEL") {
            int a, b; cin >> a >> b;
            game.duel(a, b);
        } else if (cmd == "STATS") {
            game.stats();
        }
    }

    return 0;
}