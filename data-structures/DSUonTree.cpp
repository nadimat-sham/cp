//cuet iupc 2024 - problem I - Mexy
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
const ll mod = 1000000007;

int n, a[N], cnt[N], sz[N], m[N], ans[N], bade[N], sum;
vector<int> adj[N];
bitset<N> bst;

void dfsSize(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) if (v != p) {
        dfsSize(v, u);
        sz[u] += sz[v];
    }
}

void add(int u, int p) {
    cnt[a[u]]++;
    bst.reset(a[u]);
    for (int v : adj[u]) if (v != p) {
        add(v, u);
    }
}
void remove(int u, int p) {
    cnt[a[u]]--;
    if (cnt[a[u]] == 0) bst.set(a[u]);
    for (int v : adj[u]) if (v != p) {
        remove(v, u);
    }
}
void dfsMex(int u, int p, int isBig) {
    int mx = 0, mxv = -1;
    for (int v : adj[u]) if (v != p) {
        if (sz[v] > mx) {
            mx = sz[v];
            mxv = v;
        }
    }
    for (int v : adj[u]) if (v != p && v != mxv) {
        dfsMex(v, u, 0);
    }
    if (mxv != -1) dfsMex(mxv, u, 1);
    for (int v : adj[u]) if (v != p && v != mxv) {
        add(v, u);
    }
    cnt[a[u]]++;
    bst.reset(a[u]);
    m[u] = bst._Find_first();
    if (isBig == 0) remove(u, p);
}

void dfsBadeMex(int u, int p, int isBig) {
    int mx = 0, mxv = -1;
    for (int v : adj[u]) if (v != p) {
        if (sz[v] > mx) {
            mx = sz[v];
            mxv = v;
        }
    }
    for (int v : adj[u]) if (v != p && v != mxv) {
        dfsBadeMex(v, u, 0);
    }
    if (mxv != -1) dfsBadeMex(mxv, u, 1);
    for (int v : adj[u]) if (v != p && v != mxv) {
        remove(v, u);
    }
    cnt[a[u]]--;
    if (cnt[a[u]] == 0) bst.set(a[u]);
    bade[u] = bst._Find_first();
    if (isBig == 0) add(u, p);
}
void dfsReroot(int u, int p) {
    for (int v : adj[u]) if (v != p) {
        sum -= m[v];
        sum += bade[v];
        ans[v] = sum;
        dfsReroot(v, u);
        sum -= bade[v];
        sum += m[v];
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bst.set();
    dfsSize(1, 0);
    dfsMex(1, 0, 1);
    dfsBadeMex(1, 0, 0);
    for (int i = 1; i <= n; i++) sum += m[i];
    ans[1] = sum;
    dfsReroot(1, 0);
    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
}

signed main() {
    InTheNameofAllah int t = 1;
    // cin>> t;
    for (int i = 1; i <= t; i++) {
        solve();
    }
}