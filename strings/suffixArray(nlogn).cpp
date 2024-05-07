// Suffix Array (O(nlogn)) (credit: Anik Sarker)
// m = maximum possible ASCII value of a string character (alphabet size)
// also, m = maximum number of distinct character in string (when compressed)
//(1-indexed) sa[i] = starting position (0...n-1) of ith lexicographically smallest suffix in s
//(0-indexed) Rank[i] = lexicographical rank of s[i....n-1] ((i+1)th suffix by position)
// LCP[i] = longest common prefix of sa[i] & sa[i-1]
//ranks are 1 indexed (1st, 2nd, 3rd ...)
//string and suffixes are 0 indexed
#include <bits/stdc++.h>
using namespace std;

#define N 1000005

int wa[N], wb[N], wc[N], wd[N];
int sa[N], Rank[N], LCP[N];

int cmp(int *r, int a, int b, int l) {
   return r[a]==r[b] && r[a+l] == r[b+l];
}
void buildSA(string s, int *sa, int n, int m) {
   int i, j, p, *x = wa, *y = wb, *t;
   for(i=0; i<m; i++) wd[i] = 0;
   for(i=0; i<n; i++) wd[x[i] = s[i]]++;
   for(i=1; i<m; i++) wd[i] += wd[i - 1];
   for(i=n-1; i>=0; i--)sa[--wd[x[i]]]=i;
   for(j=1, p=1; p < n; j <<= 1, m = p) {
       for(p=0, i=n-j; i<n; i++)y[p++]=i;
       for(i = 0; i < n; i++)
           if(sa[i]>=j) y[p++] =sa[i] -j;
       for(i=0; i<n; i++) wc[i] =x[y[i]];
       for(i=0; i<m; i++) wd[i] = 0;
       for(i=0; i<n; i++) wd[wc[i]]++;
       for(i=1; i<m; i++) wd[i] += wd[i - 1];
       for(i=n-1; i>=0; i--) sa[--wd[wc[i]]] = y[i];
       for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
           x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
   }
}
// Kasai's LCP algorithm (O(n))
void buildLCP(string s, int *sa, int n) {
   int i, j, k = 0;
   for(i=1; i<=n; i++) Rank[sa[i]] = i;
   for (i = 0; i < n; LCP[Rank[i++]] = k)
       for (k ? k-- : 0, j = sa[Rank[i] - 1]; s[i + k] == s[j + k]; k++);
   return;
}
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    buildSA(s, sa, n + 1, 130);
    buildLCP(s, sa, n);
    for(int i=1;i<=n;i++) cout<<sa[i]<<" "; cout<<endl;
    for(int i=0;i<n;i++) cout<<Rank[i]<<" "; cout<<endl;
    for(int i=1;i<=n;i++) cout<<LCP[i]<<" ";
}