/**
 * ============================================================
 * ARENA OF RATINGS: REAL-TIME MATCHMAKING ENGINE (ULTIMATE)
 * ============================================================
 * Features:
 * - BST-based ranking system (O(h) operations)
 * - Subtree size maintenance for Rank/Kth queries
 * - Interactive Command Line Interface (CLI)
 * - Colorized Output
 * - Robust Sideways Tree Visualization
 * - File Persistence (Save/Load)
 * - Path Distance Calculation (Duel)
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream> // Parsing
#include <fstream> // File I/O
#include <vector>

using namespace std;

// --- UI COLORS & STYLING ---
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Errors / Damage
#define GREEN   "\033[32m"      // Success / Healing
#define YELLOW  "\033[33m"      // Warnings / Null cases
#define BLUE    "\033[34m"      // Info / Borders
#define MAGENTA "\033[35m"      // Special events
#define CYAN    "\033[36m"      // Commands
#define BOLD    "\033[1m"       // Emphasis

// --- 1. NODE STRUCTURE ---
struct Node {
    int rating;         // The Key (BST Ordered)
    string name;        // Player Name
    long long hp;       // Health Points
    Node *left, *right; // Children pointers
    int sz;             // Subtree size (Rank/Kth logic)

    Node(int r, string n, long long h)
        : rating(r), name(n), hp(h), left(nullptr), right(nullptr), sz(1) {}
};

// --- 2. GLOBAL UTILS ---

void clearScreen() {
    // ANSI escape code to clear screen and move cursor to top-left
    cout << "\033[2J\033[1;1H"; 
}

void printBanner() {
    cout << BOLD << CYAN;
    cout << "==========================================\n";
    cout << "   ARENA OF RATINGS: MATCHMAKING ENGINE   \n";
    cout << "==========================================\n";
    cout << RESET;
}

// --- 3. THE ARENA CLASS ---
class Arena {
private:
    Node* root;

    // --- Helper: Get Size ---
    int getSize(Node* n) {
        return n ? n->sz : 0;
    }

    // --- Helper: Update Size ---
    void updateSize(Node* n) {
        if (n) {
            n->sz = 1 + getSize(n->left) + getSize(n->right);
        }
    }

    // --- Helper: Clean Memory ---
    void _clear(Node* node) {
        if (!node) return;
        _clear(node->left);
        _clear(node->right);
        delete node;
    }

    // --- RECURSIVE LOGIC START ---

    // Insert
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

    // Find Min/Max
    Node* _findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }
    Node* _findMax(Node* node) {
        while (node && node->right) node = node->right;
        return node;
    }

    // Delete
    Node* _delete(Node* node, int r, bool &deleted) {
        if (!node) return nullptr;

        if (r < node->rating) {
            node->left = _delete(node->left, r, deleted);
        } else if (r > node->rating) {
            node->right = _delete(node->right, r, deleted);
        } else {
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
            node->rating = succ->rating;
            node->name = succ->name;
            node->hp = succ->hp;
            bool d = false;
            node->right = _delete(node->right, succ->rating, d);
        }
        updateSize(node);
        return node;
    }

    // Range
    void _range(Node* node, int L, int R, bool &foundAny) {
        if (!node) return;
        if (node->rating > L) _range(node->left, L, R, foundAny);
        if (node->rating >= L && node->rating <= R) {
            cout << BOLD << node->rating << RESET << " " << node->name << " " << node->hp << "\n";
            foundAny = true;
        }
        if (node->rating < R) _range(node->right, L, R, foundAny);
    }

    // Rank
    int _rank(Node* node, int X) {
        if (!node) return 0;
        if (X <= node->rating) return _rank(node->left, X);
        return getSize(node->left) + 1 + _rank(node->right, X);
    }

    // Kth
    Node* _kth(Node* node, int k) {
        if (!node) return nullptr;
        int leftSz = getSize(node->left);
        if (k == leftSz + 1) return node;
        if (k <= leftSz) return _kth(node->left, k);
        return _kth(node->right, k - (leftSz + 1));
    }

    // Stats
    int _height(Node* node) {
        if (!node) return -1;
        return 1 + max(_height(node->left), _height(node->right));
    }
    int _countLeaves(Node* node) {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return _countLeaves(node->left) + _countLeaves(node->right);
    }

    // Duel
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
        return node;
    }

   // --- NEW FIXED VISUALIZER ---
    // This uses smart prefixing to ensure lines connect properly
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

    // Save
    void _saveRecursive(Node* node, ofstream &file) {
        if (!node) return;
        file << node->rating << " " << node->name << " " << node->hp << "\n";
        _saveRecursive(node->left, file);
        _saveRecursive(node->right, file);
    }

public:
    Arena() : root(nullptr) {}
    ~Arena() { _clear(root); }
    
    void clearAll() {
        _clear(root);
        root = nullptr;
    }

    // --- COMMANDS ---

    // JOIN
    void join(int r, string n, long long h) {
        bool inserted = false;
        root = _insert(root, r, n, h, inserted);
        if (inserted) cout << GREEN << "JOINED" << RESET << "\n";
        else cout << YELLOW << "DUPLICATE" << RESET << "\n";
    }

    // LEAVE
    void leave(int r) {
        bool deleted = false;
        root = _delete(root, r, deleted);
        if (deleted) cout << GREEN << "LEFT" << RESET << "\n";
        else cout << RED << "NOT FOUND" << RESET << "\n";
    }

    // STATUS
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
        if (res) cout << BOLD << res->rating << RESET << " " << res->name << " " << res->hp << "\n";
        else cout << RED << "NOT FOUND" << RESET << "\n";
    }

    // DAMAGE / HEAL
    void updateHP(int r, int amt, bool isHeal) {
        Node* res = search(r);
        if (!res) { cout << RED << "NOT FOUND" << RESET << "\n"; return; }
        long long oldHP = res->hp;
        if (isHeal) {
            res->hp += amt;
            cout << GREEN << "HEALED " << res->hp << RESET << " (Was: " << oldHP << ")\n";
        } else {
            res->hp -= amt;
            if (res->hp < 0) res->hp = 0;
            cout << RED << "DAMAGED " << res->hp << RESET << " (Was: " << oldHP << ")\n";
        }
    }

    // MATCH
    void match(int X) {
        if (!root) { cout << YELLOW << "EMPTY" << RESET << "\n"; return; }
        Node *P = nullptr, *S = nullptr;
        
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

        long long distP = abs((long long)X - P->rating);
        long long distS = abs((long long)S->rating - X);

        if (distP <= distS) cout << P->rating << " " << P->name << " " << P->hp << "\n";
        else cout << S->rating << " " << S->name << " " << S->hp << "\n";
    }

    // NEXT
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

    // PREV
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

    // RANGE
    void range(int L, int R) {
        bool foundAny = false;
        _range(root, L, R, foundAny);
        if (!foundAny) cout << YELLOW << "EMPTY" << RESET << "\n";
    }

    // RANK
    void rank(int X) {
        cout << BOLD << "Rank of " << X << ": " << RESET << _rank(root, X) << "\n";
    }

    // KTH
    void kth(int k) {
        if (k < 1 || k > getSize(root)) { cout << RED << "OUT OF RANGE" << RESET << "\n"; return; }
        Node* res = _kth(root, k);
        cout << res->rating << " " << res->name << " " << res->hp << "\n";
    }

    // DUEL
    void duel(int A, int B) {
        Node* nA = search(A);
        Node* nB = search(B);
        if (!nA || !nB) { cout << RED << "NOT FOUND" << RESET << "\n"; return; }
        Node* lca = _findLCA(root, A, B);
        int dA = _getDepth(root, A, 0);
        int dB = _getDepth(root, B, 0);
        int dLCA = _getDepth(root, lca->rating, 0);
        int dist = dA + dB - (2 * dLCA);
        cout << MAGENTA << "DIST " << dist << RESET << "\n";
    }

    // STATS
    void stats() {
        cout << BLUE << "--- ARENA STATS ---" << RESET << "\n";
        cout << "PLAYERS " << getSize(root) << "\n";
        Node* minNode = _findMin(root);
        cout << "MIN " << (minNode ? to_string(minNode->rating) : "NONE") << "\n";
        Node* maxNode = _findMax(root);
        cout << "MAX " << (maxNode ? to_string(maxNode->rating) : "NONE") << "\n";
        cout << "HEIGHT " << _height(root) << "\n";
        cout << "LEAVES " << _countLeaves(root) << "\n";
        cout << BLUE << "-------------------" << RESET << "\n";
    }

    // VISUALIZER
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

    // FILE I/O
    void saveToFile(string filename) {
        ofstream outFile(filename);
        if (!outFile) { cout << RED << "Error: Create file failed" << RESET << "\n"; return; }
        _saveRecursive(root, outFile);
        outFile.close();
        cout << GREEN << "Saved to " << filename << RESET << "\n";
    }
    
    void loadFromFile(string filename) {
        ifstream inFile(filename);
        if (!inFile) { cout << RED << "Error: Open file failed" << RESET << "\n"; return; }
        clearAll();
        int r; string n; long long h;
        int count = 0;
        while (inFile >> r >> n >> h) {
            join(r, n, h);
            count++;
        }
        inFile.close();
        cout << GREEN << "Loaded " << count << " players." << RESET << "\n";
    }
};

// --- 4. TERMINAL HELPERS ---

void printHelp() {
    cout << "\n" << BOLD << "COMMAND LIST:" << RESET << "\n";
    cout << "  " << CYAN << "JOIN <r> <name> <hp>" << RESET << "  : Add player\n";
    cout << "  " << CYAN << "LEAVE <r>" << RESET << "             : Remove player\n";
    cout << "  " << CYAN << "STATUS <r>" << RESET << "            : Show info\n";
    cout << "  " << CYAN << "DAMAGE <r> <amt>" << RESET << "      : Reduce HP\n";
    cout << "  " << CYAN << "HEAL <r> <amt>" << RESET << "        : Increase HP\n";
    cout << "  " << CYAN << "MATCH <r>" << RESET << "             : Find rival\n";
    cout << "  " << CYAN << "NEXT/PREV <r>" << RESET << "         : Neighbors\n";
    cout << "  " << CYAN << "RANGE <L> <R>" << RESET << "         : List interval\n";
    cout << "  " << CYAN << "RANK <r>" << RESET << "              : Count smaller\n";
    cout << "  " << CYAN << "KTH <k>" << RESET << "               : Get k-th smallest\n";
    cout << "  " << CYAN << "DUEL <A> <B>" << RESET << "          : Graph distance\n";
    cout << "  " << CYAN << "STATS" << RESET << "                 : Diagnostics\n";
    cout << "  " << MAGENTA << "VISUAL" << RESET << "                : Draw Tree\n";
    cout << "  " << MAGENTA << "SAVE <file>" << RESET << "           : Save data\n";
    cout << "  " << MAGENTA << "LOAD <file>" << RESET << "           : Load data\n";
    cout << "  " << YELLOW << "CLEAR" << RESET << "                 : Clear screen\n";
    cout << "  " << YELLOW << "EXIT" << RESET << "                  : Quit\n\n";
}

// --- 5. MAIN ---

int main() {
    Arena arena;
    string line, cmd;
    clearScreen();
    printBanner();
    cout << "Type '" << YELLOW << "HELP" << RESET << "' for instructions.\n\n";
    while (true) {
        cout << BOLD << "Arena> " << RESET; 
        if (!getline(cin, line)) break;
        if (line.empty()) continue;
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "HELP" || cmd == "help") {
            printHelp();
        }
        else if (cmd == "EXIT" || cmd == "QUIT" || cmd == "exit" || cmd == "quit" || cmd == "q") {
            cout << BLUE << "Saving auto-backup... " << RESET;
            arena.saveToFile("autosave.txt");
            cout << "Shutting down. Goodbye!\n";
            break;
        }
        else if (cmd == "CLEAR" || cmd == "clear" || cmd == "cls" || cmd == "clr") {
            clearScreen();
            printBanner();
        }
        else if (cmd == "JOIN" || cmd == "join") {
            int r; string n; long long h;
            if (ss >> r >> n >> h) arena.join(r, n, h);
            else cout << RED << "Usage: JOIN <rating> <name> <hp>" << RESET << "\n";
        }
        else if (cmd == "LEAVE" || cmd == "leave") {
            int r;
            if (ss >> r) arena.leave(r);
            else cout << RED << "Usage: LEAVE <rating>" << RESET << "\n";
        }
        else if (cmd == "STATUS" || cmd == "status") {
            int r;
            if (ss >> r) arena.status(r);
            else cout << RED << "Usage: STATUS <rating>" << RESET << "\n";
        }
        else if (cmd == "DAMAGE" || cmd == "damage") {
            int r, amt;
            if (ss >> r >> amt) arena.updateHP(r, amt, false);
            else cout << RED << "Usage: DAMAGE <rating> <amount>" << RESET << "\n";
        }
        else if (cmd == "HEAL" || cmd == "heal") {
            int r, amt;
            if (ss >> r >> amt) arena.updateHP(r, amt, true);
            else cout << RED << "Usage: HEAL <rating> <amount>" << RESET << "\n";
        }
        else if (cmd == "MATCH" || cmd == "match") {
            int x;
            if (ss >> x) arena.match(x);
            else cout << RED << "Usage: MATCH <rating>" << RESET << "\n";
        }
        else if (cmd == "NEXT" || cmd == "next") {
            int x;
            if (ss >> x) arena.next(x);
            else cout << RED << "Usage: NEXT <rating>" << RESET << "\n";
        }
        else if (cmd == "PREV" || cmd == "prev") {
            int x;
            if (ss >> x) arena.prev(x);
            else cout << RED << "Usage: PREV <rating>" << RESET << "\n";
        }
        else if (cmd == "RANGE" || cmd == "range") {
            int l, r;
            if (ss >> l >> r) arena.range(l, r);
            else cout << RED << "Usage: RANGE <L> <R>" << RESET << "\n";
        }
        else if (cmd == "RANK" || cmd == "rank") {
            int x;
            if (ss >> x) arena.rank(x);
            else cout << RED << "Usage: RANK <rating>" << RESET << "\n";
        }
        else if (cmd == "KTH" || cmd == "kth") {
            int k;
            if (ss >> k) arena.kth(k);
            else cout << RED << "Usage: KTH <k>" << RESET << "\n";
        }
        else if (cmd == "DUAL" || cmd == "dual") {
            int a, b;
            if (ss >> a >> b) arena.duel(a, b);
            else cout << RED << "Usage: DUAL <A> <B>" << RESET << "\n";
        }
        else if (cmd == "STATS" || cmd == "stats") {
            arena.stats();
        }
        else if (cmd == "VISUAL" || cmd == "visual") {
            arena.printTree();
        }
        else if (cmd == "SAVE" || cmd == "save") {
            string file;
            if (ss >> file) arena.saveToFile(file);
            else cout << RED << "Usage: SAVE <filename.txt>" << RESET << "\n";
        }
        else if (cmd == "LOAD" || cmd == "load") {
            string file;
            if (ss >> file) arena.loadFromFile(file);
            else cout << RED << "Usage: LOAD <filename.txt>" << RESET << "\n";
        }
        else {
            cout << RED << "Unknown command: '" << cmd << "'" << RESET << "\n";
            cout << "Type 'HELP' for commands.\n";
        }
    }
    return 0;
}