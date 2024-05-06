int lg[N];

struct MnTable {
    vector<vector<ll>> mn;
    int n;
    MnTable(int n, vector<ll>& a) {
        this->n = n;
        mn = vector<vector<ll>>(n + 3, vector<ll>(18));
        buildMn(a);
    }
    void buildMn(vector<ll>& a) {
        for (int i = 1; i <= n; ++i) mn[i][0] = a[i];
        for (int k = 1; k < 18; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                mn[i][k] = min(mn[i][k - 1], mn[i + (1 << (k - 1))][k - 1]);
            }
        }
    }
    ll queryMn(int l, int r) {
        if (l > r) return inf;
        int k = lg[r - l + 1];
        return min(mn[l][k], mn[r - (1 << k) + 1][k]);
    }
};

signed main() {
    InTheNameofAllah int t;
    lg[1] = 0;
    for (int i = 2; i < N; i++) {
        lg[i] = lg[i - 1];
        lg[i] += (int)((i & (i - 1)) == 0);
    }
    cin >> t;
    while (t--) solve();
}