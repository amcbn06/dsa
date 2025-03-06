template<typename T>
struct MinFenwickTree {
    vector<T> table;
    int size;
    MinFenwickTree(int size = 0) {
        this->size = size;
        table.assign(size + 1, numeric_limits<T>::max());
    }
    void update(int i, T x) {
        for (; i <= size; i += i & -i) {
            table[i] = min(table[i], x);
        }
    }
    T get(int i) {
        T res = numeric_limits<T>::max();
        for (; i > 0; i -= i & -i) {
            res = min(res, table[i]);
        }
        return sum;
    }
};
