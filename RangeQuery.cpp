/*
===== Sparse Table =====
Used for range query in logarithmic time with idempotent func like min() with no dynamic update
*/
vector<vector<int>> table;
void buildSparseTable(vector<int> ar){
    int n = ar.size(), maxN = log2(n) + 1;
    table = vector<vector<int>> (n, vector<int> (maxN + 1));
    rep(i, n){
        table[i][0] = ar[i];
    }

    REP(i, 1, maxN + 1){
        rep(j, n - (1<<i) + 1){
            table[j][i] = min(table[j][i-1], table[j + (1<<(i-1))][i-1]);
        }
    }
}

int query(int l, int r){
    int maxN = log2(r - l + 1);

    return min(table[l][maxN], table[r - (1<<maxN) + 1][maxN]);
}

/*
===== Binary Indexed Tree / Fenwick Tree =====
Used for range query in O(log n) with dynamic update
*/
class Fenwick{
public:
    vector<int> bit;
    int size;
    
    Fenwick(int n){
        size = n;
        bit = vector<int>(n + 1, 0);
    }

    int sum(int k) {
        int s = 0;
        while (k >= 1) {
            s += bit[k];
            k -= k&-k;
        }
        return s;
    }

    void add(int k, int x) {
        while (k <= size) {
            bit[k] += x;
            k += k&-k;
        }
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

    // Lazy Prop (Need vector<int> lazy)
    void update(int rT, int l, int r, int ql, int qr, int val) {
        if(lazy[rT] != -1){
            arr[rT] = lazy[rT];
            if(l != r) lazy[rT*2] = lazy[rT*2 + 1] = lazy[rT];
            lazy[rT] = -1;
        }

        if(l > qr || r < ql) {
            return;
        } else if ( l >= ql && r <= qr ) {
            arr[rT] = val;
            if(l != r) lazy[rT*2] = lazy[rT*2 + 1] = val;
        } else {
            int mid = l + (r - l) / 2;
            update(rT * 2, l, mid, ql, qr, val);
            update(rT * 2+1, mid + 1, r, ql, qr, val);
            pushUp(rT);
        }
    } 

    int getMax(int rT, int l, int r, int ql, int qr){
        if(lazy[rT] != -1){
            arr[rT] = lazy[rT];
            if(l != r) lazy[rT*2 ] = lazy[rT*2 + 1] = lazy[rT];
            lazy[rT] = -1;
        }

        if(l > qr || r < ql) {
            return 0;
        } else if ( l >= ql && r <= qr ) {
            return arr[rT];
        } else {
            int mid = l + (r - l) / 2;
            int res1 = getMax(rT*2, l, mid, ql, qr);
            int res2 = getMax(rT*2+1, mid+1, r, ql, qr);
            return max(res1, res2);
        }
    }
};
