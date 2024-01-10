struct NodeMn {
    int lx, rx, Mid;
    NodeMn* Left;
    NodeMn* Right;
    int mn;
    NodeMn(int lx, int rx) {
        this->lx = lx, this->rx = rx, Mid = (lx + rx) / 2;
        if (lx == rx) {
            mn = b[lx];
            return;
        }
        Left = new NodeMn(lx, Mid);
        Right = new NodeMn(Mid + 1, rx);
        mn = min(Left->mn, Right->mn);
    }
    int get(int l, int r) {
        if (l <= lx && rx <= r) return mn;
        if (rx < l || r < lx) return inf; /*** check if ll or int ***/
        return min(Left->get(l, r), Right->get(l, r));
    }
    void nearestMnPre(int l, int r, int val, int& idx) {
        if (idx > 0 || rx < l || r < lx) return;
        if (l <= lx && rx <= r) {
            if (mn >= val) return;
            auto now = this;
            while (now->lx != now->rx) {
                if (now->Left->mn < val)
                    now = now->Left;
                else
                    now = now->Right;
            }
            idx = now->lx;
            return;
        }
        Left->nearestMnPre(l, r, val, idx);
        Right->nearestMnPre(l, r, val, idx);
    }
    void nearestMnSuf(int l, int r, int val, int& idx) {
        if (idx > 0 || rx < l || r < lx) return;
        if (l <= lx && rx <= r) {
            if (mn >= val) return;
            auto now = this;
            while (now->lx != now->rx) {
                if (now->Right->mn < val)
                    now = now->Right;
                else
                    now = now->Left;
            }
            idx = now->lx;
            return;
        }
        Right->nearestMnSuf(l, r, val, idx);
        Left->nearestMnSuf(l, r, val, idx);
    }
};