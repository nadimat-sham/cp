//https://lightoj.com/problem/genes-in-dna
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define endl "\n"
#define inf (1LL<<61)
//#define inf (1<<30)
#define SetBit(x, k) (x |= (1LL << k))
#define ClearBit(x, k) (x &= ~(1LL << k))
#define CheckBit(x, k) ((x>>k)&1)
#define ppcll __builtin_popcountll
#define all(x) x.begin(), x.end()
#define intPow(n, p) (ll)(pow(n, p) + 0.5)
#define InTheNameofAllah ios_base::sync_with_stdio(0); cin.tie(NULL);
#define debug(x) cout<<"["<<#x<<": "<<x<<"]\n"
#define debug2(x, y) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]\n"
#define debug3(x, y, z) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]"<<"  ["<<#z<<": "<<z<<"]\n"
#define debug4(x, y, z, k) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]"<<"  ["<<#z<<": "<<z<<"]"<<"  ["<<#k<<": "<<k<<"]\n"
#define debug5(x, y, z, k, m) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]"<<"  ["<<#z<<": "<<z<<"]"<<"  ["<<#k<<": "<<k<<"]"<<"  ["<<#m<<": "<<m<<"]\n"
#define debug6(x, y, z, k, m, n) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]"<<"  ["<<#z<<": "<<z<<"]"<<"  ["<<#k<<": "<<k<<"]"<<"  ["<<#m<<": "<<m<<"]"<<"  ["<<#n<<": "<<n<<"]\n"
 
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
//char dir[] = {'U', 'D', 'L', 'R'};
 
// int dr[] = {-1, 1, 0, 0, -1, -1, 1, 1};
// int dc[] = {0, 0, -1, 1, -1, 1, -1, 1};
// //U, D, L, R, UL, UR, DL, DR
 
const ll N = 1e5+5;
const ll mod = 1000000007;
const int A = 4;


string transform(string s) {
    string t;
    for(char c : s) {
        if(c == 'A') t += 'a';
        if(c == 'C') t += 'b';
        if(c == 'G') t += 'c';
        if(c == 'T') t += 'd';
    }
    return t;
}
vector<int> z_vals(string s) { //0 indexed
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i=1; i<n; i++) {
        if(r < i) {
            l = r = i;
            while(r < n && s[r-l] == s[r]) r++;
            r--;
            z[i] = r - l + 1;
        } else {
            int k = i - l;
            if(z[k] < r - i + 1) z[i] = z[k];
            else {
                l = i;
                while(r < n && s[r-l] == s[r]) r++;
                r--;
                z[i] = r - l + 1;
            }
        }
    }
    z[0] = n;
    return z;
}
vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

int endsHere[N], cnt[N];

void solve() {
    memset(endsHere, 0, sizeof endsHere);
    memset(cnt, 0, sizeof cnt);

    string d, g;
    cin>> d >> g;
    d = transform(d), g = transform(g);
    int n = d.size(), m = g.size();

    string revG = g;
    reverse(all(revG));

    revG.pop_back();

    auto p = prefix_function(revG);
    for(int i=0; i<m-1; i++) {
        cnt[i] = 1;
        if(p[i] > 0) cnt[i] += cnt[p[i]-1];
    }
    string revD = d;
    reverse(all(revD));
    revG = revG + "$" + revD;
    p = prefix_function(revG);

    for(int i=0; i<revD.size(); i++) {
        int inp = i + m;
        int ind = n-1-i;
        if(p[inp] > 0) endsHere[ind] = cnt[p[inp]-1];
        endsHere[ind] += endsHere[ind+1];
    }
    
    g.pop_back();
    d = g + "$" + d;
    auto z = z_vals(d);
    int ans = 0;
    for(int i=0; i<n; i++) {
        int inz = i + m;
        int l = i + 1;
        int r = i + z[inz];
        ans += endsHere[l] - endsHere[r+1];
    }
    cout<< ans << endl;
}

signed main()
{
    InTheNameofAllah
    int t = 1;
    cin>> t;
    for(int i=1; i<=t; i++) {
        cout<< "Case " << i << ": ";
        solve();
    }
}