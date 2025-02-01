struct itemType {
    /// parameters
    itemType() {

    }
    /// combining operation
    friend itemType operator+(const itemType& lhs, const itemType& rhs) {

    }
};

const itemType nullItem;

struct updateType {
    /// parameters
    updateType() {
    
    }
    /// combining operation
    friend updateType operator*(const updateType& lhs, const updateType& rhs) {

    }
    bool operator==(const updateType& other) const {

    }
};

const updateType nullUpdate;

const int nmax = 1'000'000;
int n;
itemType t[4 * nmax + 5];
updateType lazy[4 * nmax + 5];

void propagate(int node, int l, int r) {
    if (lazy[node] == nullUpdate) {
        return;
    }
    // apply update
    // push update
    if (l != r) {
        lazy[node << 1] = lazy[node] * lazy[node << 1];
        lazy[node << 1 | 1] = lazy[node] * lazy[node << 1 | 1];
    }
    lazy[node] = nullUpdate;
}

void update(int node, int l, int r, int ql, int qr, updateType qu) {
    propagate(node, l, r);
    if (r < ql || qr < l) {
        return;
    }
    if (ql <= l && r <= qr) {
        lazy[node] = qu;
        propagate(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    update(node << 1, l, mid, ql, qr, qu);
    update(node << 1 | 1, mid + 1, r, ql, qr, qu);
    t[node] = t[node << 1] + t[node << 1 | 1];
}

itemType query(int node, int l, int r, int ql, int qr) {
    propagate(node, l, r);
    if (r < ql || qr < l) {
        return nullItem;
    }
    if (ql <= l && r <= qr) {
        return t[node];
    }
    int mid = (l + r) / 2;
    return query(node << 1, l, mid, ql, qr) + query(node << 1 | 1, mid + 1, r, ql, qr);
}
