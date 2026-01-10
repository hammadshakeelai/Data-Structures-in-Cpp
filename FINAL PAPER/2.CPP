#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream> // Required for parsing lines
using namespace std;

// 1. Node Structure (As per Cheat Sheet)
struct Node {
    int rating;
    string name;
    long long hp;
    Node *left, *right;
    int sz; // Subtree size for RANK and KTH

    Node(int r, string n, long long h)
        : rating(r), name(n), hp(h), left(nullptr), right(nullptr), sz(1) {}
};

// Helper to get size safely (handles nullptr)
int getSize(Node* n) {
    return n ? n->sz : 0;
}

// Helper to update size
void updateSize(Node* n) {
    if (n) {
        n->sz = 1 + getSize(n->left) + getSize(n->right);
    }
}

class Arena {
private:
    Node* root;

    // --- Internal Recursive Helpers ---

    Node* _insert(Node* node, int r, string n, long long h, bool &inserted) {
        if (!node) {
            inserted = true;
            return new Node(r, n, h);
        }
        if (r == node->rating) {
            inserted = false; // Duplicate
            return node;
        }
        if (r < node->rating) {
            node->left = _insert(node->left, r, n, h, inserted);
        } else {
            node->right = _insert(node->right, r, n, h, inserted);
        }
        updateSize(node);
        return node;
    }

    Node* _findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* _findMax(Node* node) {
        while (node && node->right) node = node->right;
        return node;
    }

    Node* _delete(Node* node, int r, bool &deleted) {
        if (!node) return nullptr;

        if (r < node->rating) {
            node->left = _delete(node->left, r, deleted);
        } else if (r > node->rating) {
            node->right = _delete(node->right, r, deleted);
        } else {
            // Found node to delete
            deleted = true;
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
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children
            Node* succ = _findMin(node->right);
            // Copy successor data
            node->rating = succ->rating;
            node->name = succ->name;
            node->hp = succ->hp;
            // Delete successor from right subtree
            // IMPORTANT: We recursively delete the successor's OLD rating from the right
            bool dummy = false;
            node->right = _delete(node->right, succ->rating, dummy);
        }
        updateSize(node);
        return node;
    }

    void _range(Node* node, int L, int R) {
        if (!node) return;
        if (node->rating > L) _range(node->left, L, R);
        if (node->rating >= L && node->rating <= R) {
            cout << node->rating << " " << node->name << " " << node->hp << "\n";
        }
        if (node->rating < R) _range(node->right, L, R);
    }

    int _rank(Node* node, int X) {
        if (!node) return 0;
        if (X <= node->rating) return _rank(node->left, X);
        return getSize(node->left) + 1 + _rank(node->right, X);
    }

    Node* _kth(Node* node, int k) {
        if (!node) return nullptr;
        int L = getSize(node->left);
        if (k == L + 1) return node;
        if (k <= L) return _kth(node->left, k);
        return _kth(node->right, k - (L + 1));
    }

    // Structural Stats Helpers
    int _height(Node* node) {
        if (!node) return -1; // Empty height -1, Leaf 0
        return 1 + max(_height(node->left), _height(node->right));
    }

    int _countLeaves(Node* node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return _countLeaves(node->left) + _countLeaves(node->right);
    }

    // Duel / LCA Helpers
    int _getDepth(Node* node, int val, int depth) {
        if (!node) return -1;
        if (node->rating == val) return depth;
        if (val < node->rating) return _getDepth(node->left, val, depth + 1);
        return _getDepth(node->right, val, depth + 1);
    }

    Node* _findLCA(Node* node, int A, int B) {
        if (!node) return nullptr;
        if (node->rating > A && node->rating > B) return _findLCA(node->left, A, B);
        if (node->rating < A && node->rating < B) return _findLCA(node->right, A, B);
        return node; // Split point or one matches
    }

public:
    Arena() : root(nullptr) {}

    // 1) JOIN
    void join(int r, string n, long long h) {
        bool inserted = false;
        root = _insert(root, r, n, h, inserted);
        if (inserted) cout << "JOINED\n";
        else cout << "DUPLICATE\n";
    }

    // 2) LEAVE
    void leave(int r) {
        bool deleted = false;
        root = _delete(root, r, deleted);
        if (deleted) cout << "LEFT\n";
        else cout << "NOT FOUND\n";
    }

    // 3) STATUS
    Node* search(int r) {
        Node* curr = root;
        while (curr) {
            if (curr->rating == r) return curr;
            else if (r < curr->rating) curr = curr->left;
            else curr = curr->right;
        }
        return nullptr;
    }
    
    void status(int r) {
        Node* res = search(r);
        if (res) cout << res->rating << " " << res->name << " " << res->hp << "\n";
        else cout << "NOT FOUND\n";
    }

    // 4 & 5) DAMAGE / HEAL
    void updateHP(int r, int amt, bool isHeal) {
        Node* res = search(r);
        if (!res) {
            cout << "NOT FOUND\n";
            return;
        }
        if (isHeal) {
            res->hp += amt;
            cout << "HEALED " << amt << " | New HP " <<res->hp << "\n";
        } else {
            res->hp -= amt;
            if (res->hp < 0) res->hp = 0;
            cout << "DAMAGED " << amt << " | HP Remaining: "< res << "\n";
        }
    }

    // 6) MATCH
    void match(int X) {
        if (!root) {
            cout << "EMPTY\n";
            return;
        }
        Node* P = nullptr; // Predecessor
        Node* S = nullptr; // Successor
        
        // Find Predecessor
        Node* curr = root;
        while (curr) {
            if (curr->rating < X) { P = curr; curr = curr->right; }
            else curr = curr->left;
        }
        
        // Find Successor
        curr = root;
        while (curr) {
            if (curr->rating > X) { S = curr; curr = curr->left; }
            else curr = curr->right;
        }

        if (!P && !S) { cout << "EMPTY\n"; return; } // Should not happen if root exists
        if (P && !S) { cout << P->rating << " " << P->name << " " << P->hp << "\n"; return; }
        if (!P && S) { cout << S->rating << " " << S->name << " " << S->hp << "\n"; return; }

        // Both exist
        long long distP = abs((long long)X - P->rating);
        long long distS = abs((long long)S->rating - X);

        if (distP <= distS) { // Tie rule: choose lower (Predecessor)
            cout << P->rating << " " << P->name << " " << P->hp << "\n";
        } else {
            cout << S->rating << " " << S->name << " " << S->hp << "\n";
        }
    }

    // 7) NEXT
    void next(int X) {
        Node* succ = nullptr;
        Node* curr = root;
        while (curr) {
            if (curr->rating > X) { succ = curr; curr = curr->left; }
            else curr = curr->right;
        }
        if (succ) cout << succ->rating << " " << succ->name << " " << succ->hp << "\n";
        else cout << "NONE\n";
    }

    // 8) PREV
    void prev(int X) {
        Node* pred = nullptr;
        Node* curr = root;
        while (curr) {
            if (curr->rating < X) { pred = curr; curr = curr->right; }
            else curr = curr->left;
        }
        if (pred) cout << pred->rating << " " << pred->name << " " << pred->hp << "\n";
        else cout << "NONE\n";
    }

    // 9) RANGE
    void range(int L, int R) {
        // Need to check if any exist first? Cheat sheet says print EMPTY if no players in range.
        // We can check counts or just run traversal.
        // Easiest is to run traversal and use a flag if we printed nothing?
        // Actually, cheat sheet says: "If there are no players... print EMPTY".
        // Let's use a quick check logic or capture output. 
        // A clean way: check range intersection?
        // Simpler: use a static/member flag during recursion.
        bool foundAny = false;
        rangeHelper(root, L, R, foundAny);
        if (!foundAny) cout << "EMPTY\n";
    }
    
    void rangeHelper(Node* node, int L, int R, bool &foundAny) {
        if (!node) return;
        if (node->rating > L) rangeHelper(node->left, L, R, foundAny);
        if (node->rating >= L && node->rating <= R) {
            cout << node->rating << " " << node->name << " " << node->hp << "\n";
            foundAny = true;
        }
        if (node->rating < R) rangeHelper(node->right, L, R, foundAny);
    }

    // 10) RANK
    void rank(int X) {
        cout << _rank(root, X) << "\n";
    }

    // 11) KTH
    void kth(int k) {
        if (k < 1 || k > getSize(root)) {
            cout << "OUT OF RANGE\n";
            return;
        }
        Node* res = _kth(root, k);
        cout << res->rating << " " << res->name << " " << res->hp << "\n";
    }

    // 12) DUEL
    void duel(int A, int B) {
        // Check existence first
        Node* nodeA = search(A);
        Node* nodeB = search(B);
        
        if (!nodeA || !nodeB) {
            cout << "NOT FOUND\n";
            return;
        }

        Node* lca = _findLCA(root, A, B);
        int depthA = _getDepth(root, A, 0);
        int depthB = _getDepth(root, B, 0);
        int depthLCA = _getDepth(root, lca->rating, 0);

        int dist = depthA + depthB - (2 * depthLCA);
        cout << "DIST " << dist << "\n";
    }

    // 13) STATS
    void stats() {
        cout << "PLAYERS " << getSize(root) << "\n";
        
        Node* minNode = _findMin(root);
        if (minNode) cout << "MIN " << minNode->rating << "\n";
        else cout << "MIN NONE\n";

        Node* maxNode = _findMax(root);
        if (maxNode) cout << "MAX " << maxNode->rating << "\n";
        else cout << "MAX NONE\n";

        cout << "HEIGHT " << _height(root) << "\n";
        cout << "LEAVES " << _countLeaves(root) << "\n";
    }
};


void printHelp() {
    cout << "\n=== ARENA OF RATINGS: COMMAND LIST ===\n";
    cout << "  JOIN <rating> <name> <hp>  : Add a player (e.g., JOIN 50 Ares 100)\n";
    cout << "  LEAVE <rating>             : Remove a player\n";
    cout << "  STATUS <rating>            : Show player details\n";
    cout << "  DAMAGE <rating> <amount>   : Reduce player HP\n";
    cout << "  HEAL <rating> <amount>     : Increase player HP\n";
    cout << "  MATCH <rating>             : Find closest opponent\n";
    cout << "  NEXT <rating>              : Find next higher player\n";
    cout << "  PREV <rating>              : Find next lower player\n";
    cout << "  RANGE <L> <R>              : List players in rating range\n";
    cout << "  RANK <rating>              : Count players with lower rating\n";
    cout << "  KTH <k>                    : Find k-th smallest player\n";
    cout << "  DUEL <A> <B>               : Measure tree distance between ratings\n";
    cout << "  STATS                      : Show system diagnostics\n";
    cout << "  CLEAR                      : Clear the screen\n";
    cout << "  EXIT                       : Quit the program\n";
    cout << "======================================\n\n";
}

void clearScreen() {
    // Works on most Linux/Mac terminals. For Windows, use system("cls") if needed.
    cout << "\033[2J\033[1;1H"; 
}
int main() {
    Arena arena;
    string line, cmd;
    
    // Clear screen on startup for a fresh look
    clearScreen();
    cout << "Welcome to the Arena of Ratings Engine.\n";
    cout << "Type 'HELP' for a list of commands.\n\n";

    while (true) {
        // 1. Print the Prompt
        cout << "Arena> "; 
        
        // 2. Get the entire line of input (safer than cin >>)
        if (!getline(cin, line)) break; // Exit on Ctrl+D (EOF)
        if (line.empty()) continue;     // Skip empty enters

        // 3. Parse the line
        stringstream ss(line);
        ss >> cmd;

        // Convert command to uppercase for case-insensitive handling (Optional but nice)
        // transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper); 

        // 4. Command Routing
        if (cmd == "HELP") {
            printHelp();
        }
        else if (cmd == "EXIT" || cmd == "QUIT") {
            cout << "Shutting down engine... Goodbye!\n";
            break;
        }
        else if (cmd == "CLEAR") {
            clearScreen();
        }
        else if (cmd == "JOIN") {
            int r; string n; long long h;
            // Check if arguments exist
            if (ss >> r >> n >> h) {
                arena.join(r, n, h);
            } else {
                cout << "Error: Invalid arguments. Usage: JOIN <rating> <name> <hp>\n";
            }
        }
        else if (cmd == "LEAVE") {
            int r;
            if (ss >> r) arena.leave(r);
            else cout << "Error: Missing rating. Usage: LEAVE <rating>\n";
        }
        else if (cmd == "STATUS") {
            int r;
            if (ss >> r) arena.status(r);
            else cout << "Error: Missing rating. Usage: STATUS <rating>\n";
        }
        else if (cmd == "DAMAGE") {
            int r, amt;
            if (ss >> r >> amt) arena.updateHP(r, amt, false);
            else cout << "Error: Invalid args. Usage: DAMAGE <rating> <amount>\n";
        }
        else if (cmd == "HEAL") {
            int r, amt;
            if (ss >> r >> amt) arena.updateHP(r, amt, true);
            else cout << "Error: Invalid args. Usage: HEAL <rating> <amount>\n";
        }
        else if (cmd == "MATCH") {
            int x;
            if (ss >> x) arena.match(x);
            else cout << "Error: Missing rating. Usage: MATCH <rating>\n";
        }
        else if (cmd == "NEXT") {
            int x;
            if (ss >> x) arena.next(x);
            else cout << "Error: Missing rating. Usage: NEXT <rating>\n";
        }
        else if (cmd == "PREV") {
            int x;
            if (ss >> x) arena.prev(x);
            else cout << "Error: Missing rating. Usage: PREV <rating>\n";
        }
        else if (cmd == "RANGE") {
            int l, r;
            if (ss >> l >> r) arena.range(l, r);
            else cout << "Error: Invalid args. Usage: RANGE <L> <R>\n";
        }
        else if (cmd == "RANK") {
            int x;
            if (ss >> x) arena.rank(x);
            else cout << "Error: Missing rating. Usage: RANK <rating>\n";
        }
        else if (cmd == "KTH") {
            int k;
            if (ss >> k) arena.kth(k);
            else cout << "Error: Missing K. Usage: KTH <k>\n";
        }
        else if (cmd == "DUEL") {
            int a, b;
            if (ss >> a >> b) arena.duel(a, b);
            else cout << "Error: Invalid args. Usage: DUEL <A> <B>\n";
        }
        else if (cmd == "STATS") {
            arena.stats();
        }
        else {
            // 5. Invalid Command Handler
            cout << "Invalid command: '" << cmd << "'\n";
            cout << "Type 'HELP' to see the list of valid commands.\n";
        }
    }
    return 0;
}