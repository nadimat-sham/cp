// https://atcoder.jp/contests/abc340/submissions/50260700
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
using namespace std;
#define ll long long
#define int long long
#define endl "\n"
#define inf (1LL << 61)
// #define inf (1<<30)
#define pi acos(-1)
#define SetBit(x, k) (x |= (1LL << k))
#define ClearBit(x, k) (x &= ~(1LL << k))
#define CheckBit(x, k) ((x >> k) & 1)
#define ppcll __builtin_popcountll
#define all(x) x.begin(), x.end()
#define intPow(n, p) (ll)(pow(n, p) + 0.5)
#define InTheNameofAllah          \
    ios_base::sync_with_stdio(0); \
    cin.tie(NULL);
#define debug(x) cout << "[" << #x << ": " << x << "]\n"
#define debug2(x, y) cout << "[" << #x << ": " << x << "]" \
                          << "  [" << #y << ": " << y << "]\n"
#define debug3(x, y, z) cout << "[" << #x << ": " << x << "]"   \
                             << "  [" << #y << ": " << y << "]" \
                             << "  [" << #z << ": " << z << "]\n"
#define debug4(x, y, z, k) cout << "[" << #x << ": " << x << "]"   \
                                << "  [" << #y << ": " << y << "]" \
                                << "  [" << #z << ": " << z << "]" \
                                << "  [" << #k << ": " << k << "]\n"
#define debug5(x, y, z, k, m) cout << "[" << #x << ": " << x << "]"   \
                                   << "  [" << #y << ": " << y << "]" \
                                   << "  [" << #z << ": " << z << "]" \
                                   << "  [" << #k << ": " << k << "]" \
                                   << "  [" << #m << ": " << m << "]\n"
#define debug6(x, y, z, k, m, n) cout << "[" << #x << ": " << x << "]"   \
                                      << "  [" << #y << ": " << y << "]" \
                                      << "  [" << #z << ": " << z << "]" \
                                      << "  [" << #k << ": " << k << "]" \
                                      << "  [" << #m << ": " << m << "]" \
                                      << "  [" << #n << ": " << n << "]\n"

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
// char dir[] = {'U', 'D', 'L', 'R'};

// int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
// int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};
// //U, D, L, R, UL, UR, DL, DR

const ll N = 2e5 + 5;
const ll mod = 998244353;

int n, a[N], st[N], tim, par[N][20], dep[N], revSt[N], dp[N], ans;
vector<int> g[N];
vector<int> color[N];
vector<int> aux[N];

void dfs(int u, int p) {
    st[u] = ++tim;
    revSt[tim] = u;
    par[u][0] = p;
    dep[u] = dep[p] + 1;
    for (int i = 1; i < 20; i++) {
        par[u][i] = par[par[u][i - 1]][i - 1];
    }
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    for (int i = 19; i >= 0; i--) {
        if (dep[par[u][i]] >= dep[v]) u = par[u][i];
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; i--) {
        if (par[u][i] != par[v][i]) {
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}
void dfsAux(int u, int p, int c) {
    int tot = 1;
    int single = 0;
    for (int v : aux[u])
        if (v != p) {
            dfsAux(v, u, c);
            tot *= (1 + dp[v]);
            tot %= mod;
            single += dp[v];
            single %= mod;
        }

    dp[u] = tot;
    ans += tot;
    ans %= mod;
    if (a[u] != c) {
        dp[u]--;
        dp[u] += mod + mod;
        dp[u] %= mod;
        ans -= single;
        ans += mod + mod;
        ans %= mod;
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], color[a[i]].push_back(i);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    int ret = 0;
    for (int i = 1; i <= n; i++) {
        if (color[i].empty()) continue;
        sort(all(color[i]), [&](int x, int y) {
            return st[x] < st[y];
        });
        int k = color[i].size();
        for (int j = 1; j < k; j++) {
            color[i].push_back(lca(color[i][j - 1], color[i][j]));
        }
        sort(all(color[i]), [&](int x, int y) {
            return st[x] < st[y];
        });
        color[i].resize(unique(all(color[i])) - color[i].begin());
        for (int j = 1; j < color[i].size(); j++) {
            aux[lca(color[i][j - 1], color[i][j])].push_back(color[i][j]);
        }
        dfsAux(color[i][0], 0, i);
        ret += ans;
        ret %= mod;
        ans = 0;
        for (int j : color[i]) aux[j].clear(), dp[j] = 0;
    }
    cout << ret << endl;
}

signed main() {
    InTheNameofAllah int t = 1;
    // cin>> t;
    for (int i = 1; i <= t; i++) {
        solve();
    }
}