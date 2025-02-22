// Works with indicies in range [1, size]
template<typename T>
struct max_fenwick {
    vector<T> table;
    int size, base_value;
    max_fenwick(int size = 0, int base_value = numeric_limits<T>::max()) {
        this->resize(size, base_value);
    }
    void resize(int size, int base_value = numeric_limits<T>::max()) {
        this->size = size;
        this->base_value = base_value;
        table.assign(size + 1, base_value);
    }
    // a[i] = max(a[i], x)
    void update(int i, T x) {
        for (; i <= size; i += i & -i) {
            table[i] = max(table[i], x);
        }
    }
    // max(a[1...i])
    T query(int i) {
        T res = base_value;
        for (; i > 0; i -= i & -i) {
            res = max(res, table[i]);
        }
        return res;
    }
};

using fenwick = max_fenwick<int>;