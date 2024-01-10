struct Node {
    int lx, rx, Mid;
    Node* Left;
    Node* Right;
    int lazy, mn;
    Node(int lx, int rx, int arr[]) {  // arr is a global array
        this->lx = lx, this->rx = rx, Mid = (lx + rx) >> 1;
        lazy = mn = 0;
        if (lx == rx) {
            mn = arr[lx];
            return;
        }
        Left = new Node(lx, Mid, arr);
        Right = new Node(Mid + 1, rx, arr);
        mn = min(Left->mn, Right->mn);
    }
    void propagate() {
        if (lazy == 0 || lx == rx) return;
        Left->mn += lazy;
        Left->lazy += lazy;

        Right->mn += lazy;
        Right->lazy += lazy;
        lazy = 0;
    }
    void update(int l, int r, int val) {  // makePointUpdateUsing update(i,i)
        if (l <= lx && rx <= r) {
            mn += val;
            lazy += val;
            return;
        }
        if (r < lx || rx < l) return;
        propagate();
        Left->update(l, r, val);
        Right->update(l, r, val);
        mn = min(Left->mn, Right->mn);
    }
    void nearestMinAtRight(int l, int r, int val, int& pos) {
        if (pos != -1 || r < lx || rx < l) return;
        if (l <= lx && rx <= r) {
            if (mn >= val) return;
            Node* cur = this;
            while (cur->lx != cur->rx) {
                cur->propagate();
                if (cur->Left->mn < val)
                    cur = cur->Left;
                else
                    cur = cur->Right;
            }
            pos = cur->lx;
            return;
        }
        propagate();
        Left->nearestMinAtRight(l, r, val, pos);
        Right->nearestMinAtRight(l, r, val, pos);
    }
    int get(int l, int r) {  // make point query using range query get(i,i)
        if (l <= lx && rx <= r) return mn;
        if (r < lx || rx < l) return inf;
        propagate();
        return min(Left->get(l, r), Right->get(l, r));
    }
};
