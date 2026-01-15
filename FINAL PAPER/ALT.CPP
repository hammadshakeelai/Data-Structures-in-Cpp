#include <iostream>
#include <fstream>
#include <string>   // Crucial for string error
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std; // Crucial for string error

// --- CONFIGURATION & STYLING ---
const string C_RESET  = "\033[0m";
const string C_ERR    = "\033[31m"; // Red
const string C_OK     = "\033[32m"; // Green
const string C_WARN   = "\033[33m"; // Yellow
const string C_DATA   = "\033[36m"; // Cyan
const string C_TITLE  = "\033[1;34m"; // Bold Blue

// --- 1. DATA STRUCTURES ---

struct PlayerNode {
    int id;             // Originally 'rating'
    string username;    // Originally 'name'
    long long health;   // Originally 'hp'
    
    PlayerNode *leftBranch;
    PlayerNode *rightBranch;
    int subSize;        // Subtree size

    PlayerNode(int r, string n, long long h) {
        id = r;
        username = n;
        health = h;
        leftBranch = nullptr;
        rightBranch = nullptr;
        subSize = 1;
    }
};

// --- 2. MAIN ENGINE CLASS ---

class RatingEngine {
private:
    PlayerNode* rootNode;

    // -- Helper: Get size safely --
    int getSize(PlayerNode* p) {
        if (p == nullptr) return 0;
        return p->subSize;
    }

    // -- Helper: Recalculate size --
    void fixSize(PlayerNode* p) {
        if (p != nullptr) {
            p->subSize = 1 + getSize(p->leftBranch) + getSize(p->rightBranch);
        }
    }

    // -- Recursive Insert (Reference Logic) --
    void insertWorker(PlayerNode*& p, int r, string n, long long h, bool& success) {
        if (p == nullptr) {
            p = new PlayerNode(r, n, h);
            success = true;
            return;
        }
        if (r == p->id) {
            success = false; // Duplicate
            return;
        }
        
        if (r < p->id) insertWorker(p->leftBranch, r, n, h, success);
        else insertWorker(p->rightBranch, r, n, h, success);
        
        fixSize(p);
    }

    // -- Helper: Find Minimum Node --
    PlayerNode* getMinNode(PlayerNode* p) {
        while (p && p->leftBranch) p = p->leftBranch;
        return p;
    }
    
    // -- Helper: Find Maximum Node --
    PlayerNode* getMaxNode(PlayerNode* p) {
        while (p && p->rightBranch) p = p->rightBranch;
        return p;
    }

    // -- Recursive Delete --
    void deleteWorker(PlayerNode*& p, int r, bool& success) {
        if (p == nullptr) return;

        if (r < p->id) {
            deleteWorker(p->leftBranch, r, success);
        } else if (r > p->id) {
            deleteWorker(p->rightBranch, r, success);
        } else {
            // Target found
            success = true;
            
            // Case: No children or One child
            if (p->leftBranch == nullptr) {
                PlayerNode* temp = p->rightBranch;
                delete p;
                p = temp;
            } else if (p->rightBranch == nullptr) {
                PlayerNode* temp = p->leftBranch;
                delete p;
                p = temp;
            } else {
                // Case: Two children
                PlayerNode* successor = getMinNode(p->rightBranch);
                // Copy data
                p->id = successor->id;
                p->username = successor->username;
                p->health = successor->health;
                // Delete the successor node recursively
                bool tempFlag = false; // dummy flag
                deleteWorker(p->rightBranch, successor->id, tempFlag);
            }
        }
        fixSize(p);
    }

    // -- Helpers for Range, Rank, Kth --
    
    void processRange(PlayerNode* p, int minR, int maxR, bool& hit) {
        if (!p) return;
        if (p->id > minR) processRange(p->leftBranch, minR, maxR, hit);
        
        if (p->id >= minR && p->id <= maxR) {
            cout << p->id << " " << p->username << " " << p->health << endl;
            hit = true;
        }
        
        if (p->id < maxR) processRange(p->rightBranch, minR, maxR, hit);
    }

    int calculateRank(PlayerNode* p, int val) {
        if (!p) return 0;
        if (val <= p->id) return calculateRank(p->leftBranch, val);
        return getSize(p->leftBranch) + 1 + calculateRank(p->rightBranch, val);
    }

    PlayerNode* findKth(PlayerNode* p, int k) {
        if (!p) return nullptr;
        int leftSz = getSize(p->leftBranch);
        
        if (k == leftSz + 1) return p;
        if (k <= leftSz) return findKth(p->leftBranch, k);
        return findKth(p->rightBranch, k - (leftSz + 1));
    }

    // -- Structural Helpers --
    int calcHeight(PlayerNode* p) {
        if (!p) return -1;
        return 1 + max(calcHeight(p->leftBranch), calcHeight(p->rightBranch));
    }

    int countLeafNodes(PlayerNode* p) {
        if (!p) return 0;
        if (!p->leftBranch && !p->rightBranch) return 1;
        return countLeafNodes(p->leftBranch) + countLeafNodes(p->rightBranch);
    }

    // -- DUEL / Distance Helpers --
    int getNodeDepth(PlayerNode* p, int target, int currentDepth) {
        if (!p) return -1;
        if (p->id == target) return currentDepth;
        if (target < p->id) return getNodeDepth(p->leftBranch, target, currentDepth + 1);
        return getNodeDepth(p->rightBranch, target, currentDepth + 1);
    }

    PlayerNode* findLCA(PlayerNode* p, int A, int B) {
        if (!p) return nullptr;
        if (p->id > A && p->id > B) return findLCA(p->leftBranch, A, B);
        if (p->id < A && p->id < B) return findLCA(p->rightBranch, A, B);
        return p;
    }

    // -- Visualization Helper --
    void drawTree(PlayerNode* p, string indent, bool isLeft) {
        if (!p) return;
        cout << indent;
        cout << (isLeft ? "|-- " : "`-- ");
        cout << C_DATA << "[" << p->id << "] " << C_RESET << p->username << "\n";
        
        string nextIndent = indent + (isLeft ? "|   " : "    ");
        if (p->leftBranch || p->rightBranch) {
            if(p->leftBranch) drawTree(p->leftBranch, nextIndent, true);
            else drawTree(nullptr, nextIndent, true);
            
            if(p->rightBranch) drawTree(p->rightBranch, nextIndent, false);
            else drawTree(nullptr, nextIndent, false);
        }
    }

    // -- File IO Recursive --
    void saveRec(PlayerNode* p, ofstream& out) {
        if(!p) return;
        out << p->id << " " << p->username << " " << p->health << "\n";
        saveRec(p->leftBranch, out);
        saveRec(p->rightBranch, out);
    }

public:
    RatingEngine() { rootNode = nullptr; }

    // --- API FUNCTIONS ---

    void executeJoin(int r, string n, long long h) {
        bool result = false;
        insertWorker(rootNode, r, n, h, result);
        if (result) cout << C_OK << "JOINED" << C_RESET << endl;
        else cout << C_WARN << "DUPLICATE" << C_RESET << endl;
    }

    void executeLeave(int r) {
        bool result = false;
        deleteWorker(rootNode, r, result);
        if (result) cout << C_ERR << "LEFT" << C_RESET << endl;
        else cout << C_WARN << "NOT FOUND" << C_RESET << endl;
    }

    PlayerNode* find(int r) {
        PlayerNode* curr = rootNode;
        while (curr) {
            if (curr->id == r) return curr;
            if (r < curr->id) curr = curr->leftBranch;
            else curr = curr->rightBranch;
        }
        return nullptr;
    }

    void executeStatus(int r) {
        PlayerNode* p = find(r);
        if (p) cout << p->id << " " << p->username << " " << p->health << endl;
        else cout << C_WARN << "NOT FOUND" << C_RESET << endl;
    }

    void modifyHealth(int r, int amt, bool healing) {
        PlayerNode* p = find(r);
        if (!p) {
            cout << C_WARN << "NOT FOUND" << C_RESET << endl;
            return;
        }
        if (healing) {
            p->health += amt;
            cout << C_OK << "HEALED " << p->health << C_RESET << endl;
        } else {
            p->health -= amt;
            if (p->health < 0) p->health = 0;
            cout << C_ERR << "DAMAGED " << p->health << C_RESET << endl;
        }
    }

    void executeMatch(int target) {
        if (!rootNode) { cout << C_WARN << "EMPTY" << C_RESET << endl; return; }
        
        PlayerNode *floorNode = nullptr;
        PlayerNode *ceilNode = nullptr;

        // Search for floor (Predecessor)
        PlayerNode* curr = rootNode;
        while(curr) {
            if(curr->id < target) { floorNode = curr; curr = curr->rightBranch; }
            else curr = curr->leftBranch;
        }

        // Search for ceil (Successor)
        curr = rootNode;
        while(curr) {
            if(curr->id > target) { ceilNode = curr; curr = curr->leftBranch; }
            else curr = curr->rightBranch;
        }

        if(!floorNode && !ceilNode) { cout << C_WARN << "EMPTY" << C_RESET << endl; return; }
        if(floorNode && !ceilNode) { 
            cout << floorNode->id << " " << floorNode->username << " " << floorNode->health << endl; return; 
        }
        if(!floorNode && ceilNode) { 
            cout << ceilNode->id << " " << ceilNode->username << " " << ceilNode->health << endl; return; 
        }

        // Tie-breaker logic
        long long d1 = abs((long long)target - floorNode->id);
        long long d2 = abs((long long)ceilNode->id - target);

        if (d1 <= d2) cout << floorNode->id << " " << floorNode->username << " " << floorNode->health << endl;
        else cout << ceilNode->id << " " << ceilNode->username << " " << ceilNode->health << endl;
    }

    void findNext(int val) {
        PlayerNode* succ = nullptr;
        PlayerNode* curr = rootNode;
        while (curr) {
            if (curr->id > val) { succ = curr; curr = curr->leftBranch; }
            else curr = curr->rightBranch;
        }
        if (succ) cout << succ->id << " " << succ->username << " " << succ->health << endl;
        else cout << C_WARN << "NONE" << C_RESET << endl;
    }

    void findPrev(int val) {
        PlayerNode* pred = nullptr;
        PlayerNode* curr = rootNode;
        while (curr) {
            if (curr->id < val) { pred = curr; curr = curr->rightBranch; }
            else curr = curr->leftBranch;
        }
        if (pred) cout << pred->id << " " << pred->username << " " << pred->health << endl;
        else cout << C_WARN << "NONE" << C_RESET << endl;
    }

    void executeRange(int low, int high) {
        bool found = false;
        processRange(rootNode, low, high, found);
        if (!found) cout << C_WARN << "EMPTY" << C_RESET << endl;
    }

    void executeRank(int val) {
        cout << calculateRank(rootNode, val) << endl;
    }

    void executeKth(int k) {
        if (k < 1 || k > getSize(rootNode)) {
            cout << C_WARN << "OUT OF RANGE" << C_RESET << endl;
            return;
        }
        PlayerNode* res = findKth(rootNode, k);
        cout << res->id << " " << res->username << " " << res->health << endl;
    }

    void executeDuel(int A, int B) {
        if (!find(A) || !find(B)) {
            cout << C_WARN << "NOT FOUND" << C_RESET << endl;
            return;
        }
        PlayerNode* lca = findLCA(rootNode, A, B);
        int dA = getNodeDepth(rootNode, A, 0);
        int dB = getNodeDepth(rootNode, B, 0);
        int dLCA = getNodeDepth(rootNode, lca->id, 0);
        
        cout << "DIST " << (dA + dB - 2 * dLCA) << endl;
    }

    void showStats() {
        cout << "PLAYERS " << getSize(rootNode) << endl;
        
        PlayerNode* mn = getMinNode(rootNode);
        cout << "MIN " << (mn ? to_string(mn->id) : "NONE") << endl;
        
        PlayerNode* mx = getMaxNode(rootNode);
        cout << "MAX " << (mx ? to_string(mx->id) : "NONE") << endl;

        cout << "HEIGHT " << calcHeight(rootNode) << endl;
        cout << "LEAVES " << countLeafNodes(rootNode) << endl;
    }

    void visualize() {
        if (!rootNode) cout << C_WARN << "(Empty Tree)" << C_RESET << endl;
        else {
            cout << "\n" << C_TITLE << ":: SYSTEM MAP ::" << C_RESET << endl;
            drawTree(rootNode, "", true);
            cout << "\n";
        }
    }

    void saveSystem(string fname) {
        ofstream f(fname);
        if (!f) { cout << C_ERR << "File Error" << C_RESET << endl; return; }
        saveRec(rootNode, f);
        f.close();
        cout << C_OK << "Saved to " << fname << C_RESET << endl;
    }

    void loadSystem(string fname) {
        ifstream f(fname);
        if (!f) { cout << C_ERR << "File Error" << C_RESET << endl; return; }
        int r; string n; long long h;
        int c = 0;
        while (f >> r >> n >> h) {
            bool dummy = false;
            insertWorker(rootNode, r, n, h, dummy);
            if(dummy) c++;
        }
        cout << C_OK << "Restored " << c << " records." << C_RESET << endl;
    }
};

// --- 3. SYSTEM INTERFACE ---

void clearConsole() {
    cout << "\033[2J\033[1;1H"; 
}

void showHelp() {
    cout << "\n" << C_TITLE << "--- COMMAND REFERENCE ---" << C_RESET << endl;
    cout << " [Core] JOIN <id> <nm> <hp>, LEAVE <id>, STATUS <id>\n";
    cout << " [Game] DAMAGE <id> <amt>, HEAL <id> <amt>\n";
    cout << " [Srch] MATCH <id>, NEXT <id>, PREV <id>, RANGE <L> <R>\n";
    cout << " [Math] RANK <id>, KTH <k>, DUEL <A> <B>\n";
    cout << " [Sys ] STATS, VISUAL, SAVE <f>, LOAD <f>, EXIT\n\n";
}

int main() {
    // Optimization for speed
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    RatingEngine engine;
    string buffer, op;

    clearConsole();
    cout << C_TITLE << ">> Matchmaking Engine Online <<" << C_RESET << endl;
    cout << "Type 'HELP' for commands.\n\n";

    while (true) {
        cout << C_DATA << "SYS>>> " << C_RESET;
        
        // This logic handles both interactive typing and pasted file input
        if (!getline(cin, buffer)) break;
        if (buffer.empty()) continue;

        stringstream ss(buffer);
        ss >> op;

        if (op == "EXIT") break;
        else if (op == "CLEAR") clearConsole();
        else if (op == "HELP") showHelp();
        else if (op == "VISUAL") engine.visualize();
        else if (op == "STATS") engine.showStats();
        
        else if (op == "SAVE") { string f; ss >> f; engine.saveSystem(f); }
        else if (op == "LOAD") { string f; ss >> f; engine.loadSystem(f); }
        
        else if (op == "JOIN") {
            int r; string n; long long h;
            if (ss >> r >> n >> h) engine.executeJoin(r, n, h);
        }
        else if (op == "LEAVE") { int r; if(ss >> r) engine.executeLeave(r); }
        else if (op == "STATUS") { int r; if(ss >> r) engine.executeStatus(r); }
        
        else if (op == "DAMAGE") { int r,a; if(ss >> r >> a) engine.modifyHealth(r, a, false); }
        else if (op == "HEAL") { int r,a; if(ss >> r >> a) engine.modifyHealth(r, a, true); }
        
        else if (op == "MATCH") { int x; if(ss >> x) engine.executeMatch(x); }
        else if (op == "NEXT") { int x; if(ss >> x) engine.findNext(x); }
        else if (op == "PREV") { int x; if(ss >> x) engine.findPrev(x); }
        
        else if (op == "RANGE") { int l,r; if(ss >> l >> r) engine.executeRange(l, r); }
        else if (op == "RANK") { int x; if(ss >> x) engine.executeRank(x); }
        else if (op == "KTH") { int k; if(ss >> k) engine.executeKth(k); }
        else if (op == "DUEL") { int a,b; if(ss >> a >> b) engine.executeDuel(a, b); }
        
        else { cout << C_ERR << "Unknown Command." << C_RESET << endl; }
    }

    return 0;
}