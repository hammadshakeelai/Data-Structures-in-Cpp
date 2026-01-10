struct Node {
    int rating;
    std::string name;
    long long hp; // use long long to be safe
    Node *left, *right;
    int sz; // subtree size (for KTH and RANK)
    Node(int r, std::string n, long long h)
    : rating(r), name(n), hp(h), left(nullptr), right(nullptr), sz(1) {}
};//root = deletion(root,)
Node* deleteN(Node* temproot,int val){
    if (temproot == nullptr){
        return nullptr;// temproot return karo ya kuch bhi hai wo khali hi deletion not possible 
    }
    if(val == temproot->val){
        return temproot;
    }
    if(val < temproot->val){
        temproot->left = deleteN(temproot->left,val);
    }
    if(val > temproot->val){
        temproot->left = deleteN(temproot->left,val);
    }
        if(node->left == nullptr && node->right == nullptr){//agar bacghe nai hy tuo bas dlete or retun null
            delete node;
            return nullptr;
        }
        else if(node->left != nullptr && node->right != nullptr){//dono bache hay
            Node* succ = findsuccessor(root,node->val);//nasdeek bacha find karo
            Node* succPar = parent(succ);//osko baap ko dhondo
            if(succ->right != nullptr){// agar oska right wala bacha hai 
                succPar->left = succ->right;//tuo iske baap ko iska bacha pakra do
            succ->left = node->left;//ab nasdek bache ne hameri delete hone wale node ke bacho ko adopt karlia
            succ->right = node->right;
            delete node;//or wo khud mar gaya
            return succ;//ye reurn gogaya for correct place ment 
        }
        else if(node->left != nullptr){
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else if(node->right != nullptr){
            Node* temp = node->right;
            delete node;
            return temp;
        }
}