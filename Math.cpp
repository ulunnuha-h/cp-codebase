// Rumus deret n*(n+1)
// Rumus deret kuadrat (n*(n+1)*(2n+1))/6
// Rumus deret kubik (n^2*(n+1)^2)/4

// ===== Power function with modulo ===== //
ll powMod(ll x, ll y) {
    ll res = 1;
    x %= MOD;
    while (y) {
        if (y & 1) {
            res = (res * x) % MOD;
        }
        y >>= 1;
        x = (x * x) % MOD;
    }
    return res;
}

// ===== Matrix multiplication ===== //
void multiMatrix(vvi& a, vvi& b){
    int dima = a.size(), dimb = b[0].size();

    if(a[0].size() == b.size()){
        int dim = a[0].size();
        vvi res(dima, vi(dimb, 0));
        
        for(int i = 0 ; i < dima ; i++){
            for(int j = 0 ; j < dimb ; j++){
                for(int k = 0 ; k < dim; k++){
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        a = res;
    }
}
    
// ===== Power function for matrix ===== //    
void powMatrix(vvi& res, long long d){
    vvi base = res;
    while(d){
        if(d & 1){
            multiMatrix(res, base);
        }
        d = d >> 1;
        multiMatrix(base, base);
    }
}

// ===== Get angle value from 2 points in degree ===== //
double getAngle(pii a, pii b) {
    double dot = (a.fi * b.fi) + (a.se * b.se);
    double m1 = hypot(a.fi, a.se);
    double m2 = hypot(b.fi, b.se);

    double angleRad = acos(dot / (m1 * m2));
    double angleDeg = angleRad * (180.0 / M_PI);
    return (a.fi < 0 ? 360 - angleDeg : angleDeg);
}

// ===== Get Combination to select i from n -> C(n, i) ===== //
ll combMod(int n, int i) {
    long long res = fact[n];
    long long div = fact[n-i] * fact[i];
    div %= MOD;  div = powMod(div, MOD - 2, MOD);
    return (res * div) % MOD;
}

// ===== Precompute Combination using DP ===== //
void precomputeCombination(vector<vector<ll>>& nCr){
    int n = nCr.size();
    nCr[0][0] = 1ll;
    for (int i = 1; i < n; i++){
        nCr[i][0] = 1ll;
        for (int j = 1; j <= i; j++){
            nCr[i][j] = nCr[i-1][j] + nCr[i-1][j-1];
        }
    }
}