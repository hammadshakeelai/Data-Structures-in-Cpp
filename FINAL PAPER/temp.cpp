#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream> // Required for parsing lines
#include <fstream> // Required for file handling

using namespace std;

// --- UI COLORS ---
#define RESET   "\033[0m"
#define RED     "\033[31m"      // For Errors / Damage
#define GREEN   "\033[32m"      // For Success / Healing
#define YELLOW  "\033[33m"      // For Warnings / UI
#define BLUE    "\033[34m"      // For Info
#define CYAN    "\033[36m"      // For Commands
#define BOLD    "\033[1m"       // For Headers

// --- 1. Node Structure ---
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

// --- 2. The Arena Class ---
class Arena {
private:
    Node* root;

    // --- Private Recursive Helpers ---

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
            bool dummy = false;
            node->right = _delete(node->right, succ->rating, dummy);
        }
        updateSize(node);
        return node;
    }

    void _range(Node* node, int L, int R, bool &foundAny) {
        if (!node) return;
        if (node->rating > L) _range(node->left, L, R, foundAny);
        if (node->rating >= L && node->rating <= R) {
            cout << node->rating << " " << node->name << " " << node->hp << "\n";
            foundAny = true;
        }
        if (node->rating < R) _range(node->right, L, R, foundAny);
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

    // Visualization Recursive Helper
    void _printDirectoryStyle(Node* node, string prefix, bool isTail) {
        // Print current node
        cout << prefix;
        cout << (isTail ? "|__ " : "---- ");
        cout << BOLD << "[" << node->rating << "] " << RESET 
             << node->name << " " << CYAN << "(" << node->hp << "HP)" << RESET << "\n";
        
        // Calculate prefix for children
        // If I am the tail, my children don't need a vertical bar above them.
        // If I am NOT the tail, my children need a vertical bar passing through me.
        string childPrefix = prefix + (isTail ? "    " : "|   ");

        // Logic to determine who is the "Tail" (last child)
        if (node->left && node->right) {
            // Both exist: Left is NOT tail, Right IS tail
            _printDirectoryStyle(node->left, childPrefix, false);
            _printDirectoryStyle(node->right, childPrefix, true);
        } else if (node->left) {
            // Only Left exists: It becomes the tail
            _printDirectoryStyle(node->left, childPrefix, true);
        } else if (node->right) {
            // Only Right exists: It becomes the tail
            _printDirectoryStyle(node->right, childPrefix, true);
        }
    }

    // Save Recursive Helper
    void _saveRecursive(Node* node, ofstream &file) {
        if (!node) return;
        // Pre-order traversal for saving structure
        file << node->rating << " " << node->name << " " << node->hp << "\n";
        _saveRecursive(node->left, file);
        _saveRecursive(node->right, file);
    }

public:
    Arena() : root(nullptr) {}

    // --- Public Operations ---

    // 1) JOIN
    void join(int r, string n, long long h) {
        bool inserted = false;
        root = _insert(root, r, n, h, inserted);
        if (inserted) cout << GREEN << "JOINED" << RESET << "\n";
        else cout << YELLOW << "DUPLICATE" << RESET << "\n";
    }

    // 2) LEAVE
    void leave(int r) {
        bool deleted = false;
        root = _delete(root, r, deleted);
        if (deleted) cout << RED << "LEFT" << RESET << "\n";
        else cout << YELLOW << "NOT FOUND" << RESET << "\n";
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
        if (res) cout << BOLD << res->rating << " " << res->name << " " << res->hp << RESET << "\n";
        else cout << YELLOW << "NOT FOUND" << RESET << "\n";
    }

    // 4 & 5) DAMAGE / HEAL
    void updateHP(int r, int amt, bool isHeal) {
        Node* res = search(r);
        if (!res) {
            cout << YELLOW << "NOT FOUND" << RESET << "\n";
            return;
        }
        if (isHeal) {
            res->hp += amt;
            cout << GREEN << "HEALED " << res->hp << RESET << "\n";
        } else {
            res->hp -= amt;
            if (res->hp < 0) res->hp = 0;
            cout << RED << "DAMAGED " << res->hp << RESET << "\n";
        }
    }

    // 6) MATCH
    void match(int X) {
        if (!root) {
            cout << YELLOW << "EMPTY" << RESET << "\n";
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

        if (!P && !S) { cout << YELLOW << "EMPTY" << RESET << "\n"; return; }
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
        else cout << YELLOW << "NONE" << RESET << "\n";
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
        else cout << YELLOW << "NONE" << RESET << "\n";
    }

    // 9) RANGE
    void range(int L, int R) {
        bool foundAny = false;
        _range(root, L, R, foundAny);
        if (!foundAny) cout << YELLOW << "EMPTY" << RESET << "\n";
    }
    
    // 10) RANK
    void rank(int X) {
        cout << _rank(root, X) << "\n";
    }

    // 11) KTH
    void kth(int k) {
        if (k < 1 || k > getSize(root)) {
            cout << YELLOW << "OUT OF RANGE" << RESET << "\n";
            return;
        }
        Node* res = _kth(root, k);
        cout << res->rating << " " << res->name << " " << res->hp << "\n";
    }

    // 12) DUEL
    void duel(int A, int B) {
        Node* nodeA = search(A);
        Node* nodeB = search(B);
        
        if (!nodeA || !nodeB) {
            cout << YELLOW << "NOT FOUND" << RESET << "\n";
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
        cout << BLUE << "PLAYERS " << getSize(root) << RESET << "\n";
        
        Node* minNode = _findMin(root);
        if (minNode) cout << "MIN " << minNode->rating << "\n";
        else cout << "MIN NONE\n";

        Node* maxNode = _findMax(root);
        if (maxNode) cout << "MAX " << maxNode->rating << "\n";
        else cout << "MAX NONE\n";

        cout << "HEIGHT " << _height(root) << "\n";
        cout << "LEAVES " << _countLeaves(root) << "\n";
    }

    // --- NEW: Visualizer ---
    void printTree() {
        if (!root) { cout << YELLOW << "(Empty Arena)\n" << RESET; return; }
        cout << "\n" << BOLD << "--- VISUAL TOPOLOGY ---" << RESET << "\n";
        
        // Print Root manually first
        cout << BOLD << "[" << root->rating << "] " << RESET 
             << root->name << " " << CYAN << "(" << root->hp << "HP)" << RESET << "\n";
        
        // Trigger recursive printer for children
        if (root->left && root->right) {
            _printDirectoryStyle(root->left, "", false); // Left is NOT tail
            _printDirectoryStyle(root->right, "", true); // Right IS tail
        } else if (root->left) {
            _printDirectoryStyle(root->left, "", true);  // Only child is tail
        } else if (root->right) {
            _printDirectoryStyle(root->right, "", true); // Only child is tail
        }
        cout << "-----------------------\n";
    }

    // --- NEW: Persistence ---
    void saveToFile(string filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cout << RED << "Error: Could not create file " << filename << RESET << "\n";
            return;
        }
        _saveRecursive(root, outFile);
        outFile.close();
        cout << GREEN << "System saved to " << filename << RESET << "\n";
    }

    void loadFromFile(string filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << RED << "Error: Could not open file " << filename << RESET << "\n";
            return;
        }
        
        int r; string n; long long h;
        int count = 0;
        while (inFile >> r >> n >> h) {
            // Using internal insert to avoid printing "JOINED" for every load
            bool inserted = false;
            root = _insert(root, r, n, h, inserted);
            if(inserted) count++;
        }
        inFile.close();
        cout << GREEN << "Loaded " << count << " players from " << filename << RESET << "\n";
    }
};

// --- 3. Global UI Helpers ---

void printHelp() {
    cout << "\n" << BOLD << "=== ARENA OF RATINGS: COMMAND LIST ===" << RESET << "\n";
    cout << "  " << CYAN << "VISUAL" << RESET << "                 : Draw the tree structure\n";
    cout << "  " << CYAN << "SAVE <file>" << RESET << "            : Save arena to disk\n";
    cout << "  " << CYAN << "LOAD <file>" << RESET << "            : Load arena from disk\n";
    cout << "  " << CYAN << "JOIN <r> <n> <h>" << RESET << "      : Add a player\n";
    cout << "  " << CYAN << "LEAVE <r>" << RESET << "             : Remove a player\n";
    cout << "  " << CYAN << "STATUS <r>" << RESET << "            : Show player details\n";
    cout << "  " << CYAN << "DAMAGE <r> <a>" << RESET << "        : Reduce player HP\n";
    cout << "  " << CYAN << "HEAL <r> <a>" << RESET << "          : Increase player HP\n";
    cout << "  " << CYAN << "MATCH <r>" << RESET << "             : Find closest opponent\n";
    cout << "  " << CYAN << "NEXT <r>" << RESET << "              : Find next higher player\n";
    cout << "  " << CYAN << "PREV <r>" << RESET << "              : Find next lower player\n";
    cout << "  " << CYAN << "RANGE <L> <R>" << RESET << "         : List players in range\n";
    cout << "  " << CYAN << "RANK <r>" << RESET << "              : Count players with lower rating\n";
    cout << "  " << CYAN << "KTH <k>" << RESET << "               : Find k-th smallest player\n";
    cout << "  " << CYAN << "DUEL <A> <B>" << RESET << "          : Measure tree distance\n";
    cout << "  " << CYAN << "STATS" << RESET << "                 : Show system diagnostics\n";
    cout << "  " << CYAN << "CLEAR" << RESET << "                 : Clear the screen\n";
    cout << "  " << CYAN << "EXIT" << RESET << "                  : Quit the program\n";
    cout << "======================================\n\n";
}

void clearScreen() {
    // ANSI code to clear screen
    cout << "\033[2J\033[1;1H"; 
}

// --- 4. Main Loop ---

int main() {
    // --- FAST I/O (As required by Exam Cheat Sheet) ---
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Arena arena;
    string line, cmd;
    
    // Clear screen on startup
    clearScreen();
    cout << BOLD << BLUE << "Welcome to the Arena of Ratings Engine." << RESET << "\n";
    cout << "Type '" << YELLOW << "HELP" << RESET << "' for a list of commands.\n\n";

    while (true) {
        // 1. Print the Prompt
        // IMPORTANT: We must manually FLUSH because cin.tie(nullptr) stops auto-flushing.
        cout << BOLD << "Arena> " << RESET << flush; 
        
        // 2. Get the entire line
        if (!getline(cin, line)) break; // Exit on EOF
        if (line.empty()) continue;     // Skip empty lines

        // 3. Parse the line
        stringstream ss(line);
        ss >> cmd;

        // 4. Command Routing
        if (cmd == "HELP") {
            printHelp();
        }
        else if (cmd == "EXIT" || cmd == "QUIT") {
            cout << GREEN << "Saving autosave... " << RESET;
            arena.saveToFile("autosave.txt");
            cout << "Shutting down engine... Goodbye!\n";
            break;
        }
        else if (cmd == "CLEAR") {
            clearScreen();
        }
        else if (cmd == "VISUAL") {
            arena.printTree();
        }
        else if (cmd == "SAVE") {
            string file;
            if (ss >> file) arena.saveToFile(file);
            else cout << RED << "Error: Usage SAVE <filename>" << RESET << "\n";
        }
        else if (cmd == "LOAD") {
            string file;
            if (ss >> file) arena.loadFromFile(file);
            else cout << RED << "Error: Usage LOAD <filename>" << RESET << "\n";
        }
        else if (cmd == "JOIN") {
            int r; string n; long long h;
            if (ss >> r >> n >> h) arena.join(r, n, h);
            else cout << RED << "Error: Usage JOIN <rating> <name> <hp>" << RESET << "\n";
        }
        else if (cmd == "LEAVE") {
            int r;
            if (ss >> r) arena.leave(r);
            else cout << RED << "Error: Usage LEAVE <rating>" << RESET << "\n";
        }
        else if (cmd == "STATUS") {
            int r;
            if (ss >> r) arena.status(r);
            else cout << RED << "Error: Usage STATUS <rating>" << RESET << "\n";
        }
        else if (cmd == "DAMAGE") {
            int r, amt;
            if (ss >> r >> amt) arena.updateHP(r, amt, false);
            else cout << RED << "Error: Usage DAMAGE <rating> <amount>" << RESET << "\n";
        }
        else if (cmd == "HEAL") {
            int r, amt;
            if (ss >> r >> amt) arena.updateHP(r, amt, true);
            else cout << RED << "Error: Usage HEAL <rating> <amount>" << RESET << "\n";
        }
        else if (cmd == "MATCH") {
            int x;
            if (ss >> x) arena.match(x);
            else cout << RED << "Error: Usage MATCH <rating>" << RESET << "\n";
        }
        else if (cmd == "NEXT") {
            int x;
            if (ss >> x) arena.next(x);
            else cout << RED << "Error: Usage NEXT <rating>" << RESET << "\n";
        }
        else if (cmd == "PREV") {
            int x;
            if (ss >> x) arena.prev(x);
            else cout << RED << "Error: Usage PREV <rating>" << RESET << "\n";
        }
        else if (cmd == "RANGE") {
            int l, r;
            if (ss >> l >> r) arena.range(l, r);
            else cout << RED << "Error: Usage RANGE <L> <R>" << RESET << "\n";
        }
        else if (cmd == "RANK") {
            int x;
            if (ss >> x) arena.rank(x);
            else cout << RED << "Error: Usage RANK <rating>" << RESET << "\n";
        }
        else if (cmd == "KTH") {
            int k;
            if (ss >> k) arena.kth(k);
            else cout << RED << "Error: Usage KTH <k>" << RESET << "\n";
        }
        else if (cmd == "DUEL") {
            int a, b;
            if (ss >> a >> b) arena.duel(a, b);
            else cout << RED << "Error: Usage DUEL <A> <B>" << RESET << "\n";
        }
        else if (cmd == "STATS") {
            arena.stats();
        }
        else {
            cout << RED << "Invalid command: '" << cmd << "'" << RESET << "\n";
            cout << "Type 'HELP' for a list of valid commands.\n";
        }
    }
    return 0;
}