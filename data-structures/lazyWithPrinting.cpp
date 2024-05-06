struct SegTree {
    vector<int> lx, rx, Left, Right, cnt;
    vector<ll> mx, lazy;
    SegTree(int l, int r) {
        newNode(l, r);
    }
    int newNode(int l, int r) {
        int u = lx.size();
        lx.eb(l), rx.eb(r), Left.eb(0), Right.eb(0), mx.eb(0), lazy.eb(0), cnt.eb(0);
        if (l == r) {
            mx[u] = b[l];
            cnt[u] = 1;
            return u;
        }
        int mid = (l + r) >> 1;
        Left[u] = newNode(l, mid);
        Right[u] = newNode(mid + 1, r);
        recalc(u);
        return u;
    }
    void recalc(int u) {
        mx[u] = max(mx[Left[u]], mx[Right[u]]);
        cnt[u] = 0;
        if (mx[u] == mx[Left[u]]) cnt[u] += cnt[Left[u]];
        if (mx[u] == mx[Right[u]]) cnt[u] += cnt[Right[u]];
    }
    void relax(int u, ll val) {
        mx[u] += val;
        lazy[u] += val;
    }
    void propagate(int u) {
        if (lazy[u] == 0 || lx[u] == rx[u]) return;
        relax(Left[u], lazy[u]);
        relax(Right[u], lazy[u]);
        lazy[u] = 0;
    }
    void add(int u, int l, int r, int val) {
        if (l <= lx[u] && rx[u] <= r) {
            mx[u] += val;
            lazy[u] += val;
            return;
        }
        if (rx[u] < l || r < lx[u]) return;
        propagate(u);
        add(Left[u], l, r, val);
        add(Right[u], l, r, val);
        recalc(u);
    }
    pair<ll, int> get(int u, int l, int r) {
        if (l <= lx[u] && rx[u] <= r) return mp(mx[u], cnt[u]);
        if (r < lx[u] || rx[u] < l) return mp(-inf, 0);
        propagate(u);
        auto fromL = get(Left[u], l, r), fromR = get(Right[u], l, r);
        if (fromL < fromR) swap(fromL, fromR);
        if (fromL.first == fromR.first) fromL.second += fromR.second;
        return fromL;
    }
    void print() {
        vector<bool> lst;
        print(0, lst);
    }
    void print(int x, vector<bool> &lst) {
        for (int i = 0; i < ((int)lst.size()) - 1; i++) {
            if (lst[i])
                cout << "   ";
            else
                cout << "|  ";
        }
        if (!lst.empty()) cout << "|--";

        cout << "(" << lx[x] << ' ' << rx[x] << ") " << mx[x] << " " << lazy[x] << " " << cnt[x] << '\n';

        lst.push_back(false);
        if (Left[x]) {
            print(Left[x], lst);
            lst.back() = true;
            print(Right[x], lst);
        }
        lst.pop_back();
        return;
    }
};