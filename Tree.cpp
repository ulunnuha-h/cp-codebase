// ===== Binary Search Tree ===== //
struct Node{
    int val;
    Node *left, *right;

    Node(int init){
        val = init;
        left = right = nullptr;
    }
};

class Tree{
    private:
        Node *root;
    public:
        Tree(){
            root = nullptr;
        }
        void insert(int n){
            Node *cur = root;
            if(cur == nullptr){
                root = new Node(n);
            } else {
                while(true){
                    if(n > cur->val){
                        if(cur->right == nullptr){
                            cur->right = new Node(n);
                            break;
                        } else cur = cur->right;
                    } else {
                        if(cur->left == nullptr){
                            cur->left = new Node(n);
                            break;
                        } else cur = cur->left;
                    }
                }
            }
        }
        Node* getRoot(){
            return root;
        }
};