/*
===== Binary Search Tree =====
A tree that has two children for each node
*/
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

/*
===== Segment Tree =====
Used for range query in logarithmic time when updateing just one value
*/
class SegmentTree {
public:
    vector<int> arr;
    int size;

    SegmentTree(vector<int>& nums) {
        size = nums.size();
        arr.resize(4 * size);
        if (size > 0) {
            build(1, 0, size - 1, nums);
        }
    }

    void pushUp(int rT) {
        arr[rT] = arr[2 * rT] + arr[2 * rT + 1];
    }

    void build(int rT, int l, int r, vector<int>& nums) {
        if (l == r) {
            arr[rT] = nums[l];
        } else {
            int mid = l + (r - l) / 2;
            build(2 * rT, l, mid, nums);
            build(2 * rT + 1, mid + 1, r, nums);
            pushUp(rT);
        }
    }
    
    void update(int rT, int l, int r, int idx, int val) {
        if (l == r) {
            arr[rT] = val;
        } else {
            int mid = l + (r - l) / 2;
            if (idx <= mid) {
                update(rT * 2, l, mid, idx, val);
            } else {
                update(rT * 2 + 1, mid + 1, r, idx, val);
            }
            pushUp(rT);
        }
    }

    int sum(int rT, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return arr[rT];

        int mid = l + (r - l) / 2;
        return sum(rT * 2, l, mid, ql, qr) + sum(rT * 2 + 1, mid + 1, r, ql, qr);
    }
};


/*
===== Segment Tree (Lazy Propagation) =====
Used for range query in logarithmic time when updating in range
*/
class SegmentTree {
public:
    vector<node> arr;
    vector<deque<char>> lz;

    SegmentTree(int n) {
        arr.resize(4 * n);
        lz = vector<deque<char>>(4*n);
        if (n > 0) build(1, 0, n - 1);
    }

    void build(int rT, int l, int r) {
        arr[rT] = node();
        if (l != r) {
            int mid = l + (r - l) / 2;
            build(2 * rT, l, mid);
            build(2 * rT + 1, mid + 1, r);
        }
    }

    void pushChild(int rT, int l, int r, deque<char> temp){
        while(!temp.empty()){
            if(lz[rT].empty()){
                lz[rT].push_back(temp.front());
            } else if(lz[rT].back() == '~'){
                if(temp.front() != '~') lz[rT].push_back(temp.front());
                else lz[rT].pop_back();
            } else {
                if(temp.front() != '~') lz[rT].back() = temp.front();
                else lz[rT].push_back(temp.front());
            }

            temp.pop_front();
        }

        while(lz[rT].size() > 4) lz[rT].pop_front();
    }
    
    void pushDown(int rT, int l, int r){
        if(lz[rT].empty()) return;
        if(l < r){
            int m = (l+r)/2;
            pushChild(rT * 2, l, m, lz[rT]);
            pushChild(rT * 2 + 1, m+1, r, lz[rT]);
        }

        for(auto i : lz[rT]){
            if(i == '~') swap(arr[rT].F, arr[rT].B);
            else arr[rT].F = i;
        }

        lz[rT].clear();
    }

    void push(int rT, char c){
        if(lz[rT].empty()) lz[rT].pb(c);
        else{
            if(c == '~'){
                if(lz[rT].back() != '~') lz[rT].push_back(c);
                else lz[rT].pop_back();
            } else {
                if(lz[rT].back() != '~') lz[rT].back() = c;
                else lz[rT].push_back(c);
            }
        }

        while(lz[rT].size() > 4) lz[rT].pop_front();
    }

    void update(int rT, int l, int r, int ql, int qr, char c) {
        if(l > qr || r < ql) return;

        if(ql <= l && qr >= r) push(rT, c);
        if(!lz[rT].empty()) pushDown(rT, l, r);
        if(ql > l || qr < r){
            int mid = (l + r) / 2;
            update(rT * 2, l, mid, ql, qr, c);
            update(rT * 2 + 1, mid+1, r, ql, qr, c);
        }
    }

    void print(int rT, int l, int r, bool isF){
        if(!lz[rT].empty()) pushDown(rT, l, r);

        if(l == r) cout<<(isF ? arr[rT].F : arr[rT].B);
        else{
            int mid = (l + r) / 2;
            print(rT * 2, l, mid, isF);
            print(rT * 2 + 1, mid + 1, r, isF);
        }
    }

};