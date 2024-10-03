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

// ===== Factorial Precomputation ===== //
long long fact[N];
void initfact() {
    fact[0] = 1;
    for(int i = 1; i < N; i++) {
        fact[i] = (fact[i-1] * i);
        fact[i] %= MOD;
    }
}

// ===== Get Combination to select i from n -> C(n, i) ===== //
ll combMod(int n, int i) {
    long long res = fact[n];
    long long div = fact[n-i] * fact[i];
    div %= MOD;  div = powMod(div, MOD - 2, MOD);
    return (res * div) % MOD;
}

// ===== Get Combination without using factorial ===== //
ll comb(ll n, ll r){
    if(r > n) return 0;
    if(r == 0 || r == n) return 1;
    if(r > n - r) r = n - r;

    ll res = 1;
    rep(i, r){
        res *= (n-i);
        res /= (i+1);
    }
    return res;
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

// ===== Euler's Totient Precomputation ===== //
// Calculate how many positive number less than N that is coprime with N
 int i, j;
    for(i = 0;i < MAX;++i)
        toti[i] = i;
    for(i = 2;i < MAX;++i)
    {
        if(toti[i] == i)
        {
            toti[i] = i - 1;
            for(j = 2*i;j < MAX;j += i)
                toti[j] -= (toti[j] / i);
        }
    }


// ===== Sieve of Eratosthenes ===== //
// Pre calculate all Prime numbers
vector<bool> SieveOfEratosthenes(int n){
    vector<bool> prime(n+1, true);
    prime[0] = prime[1] = false;
 
    for (int p = 2; p * p <= n; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
 
    return prime;
}