struct NodeMx {
    int lx, rx, Mid;
    NodeMx* Left;
    NodeMx* Right;
    int mx;
    NodeMx(int lx, int rx) {
        this->lx = lx, this->rx = rx, Mid = (lx + rx) / 2;
        if (lx == rx) {
            mx = a[lx];
            return;
        }
        Left = new NodeMx(lx, Mid);
        Right = new NodeMx(Mid + 1, rx);
        mx = max(Left->mx, Right->mx);
    }
    int get(int l, int r) {
        if (l <= lx && rx <= r) return mx;
        if (rx < l || r < lx) return -inf; /*** check if ll or int ***/
        return max(Left->get(l, r), Right->get(l, r));
    }
    void nearestMxPre(int l, int r, int val, int& idx) {
        if (idx > 0 || rx < l || r < lx) return;
        if (l <= lx && rx <= r) {
            if (mx <= val) return;
            auto now = this;
            while (now->lx != now->rx) {
                if (now->Left->mx > val)
                    now = now->Left;
                else
                    now = now->Right;
            }
            idx = now->lx;
            return;
        }
        Left->nearestMxPre(l, r, val, idx);
        Right->nearestMxPre(l, r, val, idx);
    }
    void nearestMxSuf(int l, int r, int val, int& idx) {
        if (idx > 0 || rx < l || r < lx) return;
        if (l <= lx && rx <= r) {
            if (mx <= val) return;
            auto now = this;
            while (now->lx != now->rx) {
                if (now->Right->mx > val)
                    now = now->Right;
                else
                    now = now->Left;
            }
            idx = now->lx;
            return;
        }
        Right->nearestMxSuf(l, r, val, idx);
        Left->nearestMxSuf(l, r, val, idx);
    }
};
