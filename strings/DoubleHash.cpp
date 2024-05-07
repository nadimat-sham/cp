// https://codeforces.com/contest/1326/problem/D2
struct DoubleHash {
    static const int m[2];
    static vector<int> power[2];
    static int p;
    vector<int> pre[2];
    DoubleHash(const string& s) {  // 0 based string, pre = {0, a0, a1p, a2p2, a3p3, ..., a_n-1p_n-1}
        const int n = s.size();
        for (int i = 0; i < 2; i++) {
            pre[i] = vector<int>(n + 1);
            while (power[i].size() <= n) power[i].push_back((ll)power[i].back() * p % m[i]);
            for (int j = 1; j <= n; j++) pre[i][j] = ((ll)pre[i][j - 1] + (ll)power[i][j - 1] * s[j - 1]) % m[i];
        }
    }
    pair<int, int> operator()(const int pos, const int len, const int mxPow) {
        vector<int> hash(2);
        for (int i = 0; i < 2; i++) {
            hash[i] = (ll)(pre[i][pos + len] - pre[i][pos]) * power[i][mxPow - pos] % m[i];
            if (hash[i] < 0) hash[i] += m[i];
        }
        return make_pair(hash[0], hash[1]);
    }
    static int gen_base(const int before, const int after) {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 mt_rand(seed);
        int base = std::uniform_int_distribution<int>(before + 1, after)(mt_rand);
        return base % 2 == 0 ? base - 1 : base;
    }
};
const int DoubleHash::m[] = {(int)1e9 + 9, (int)1e9 + 123};
vector<int> DoubleHash::power[] = {{1}, {1}};
int DoubleHash::p((int)1e9 + 7);
