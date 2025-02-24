template<typename T>
struct FenwickTree {
    vector<T> table;
    int size;
    FenwickTree(int size = 0) {
        this->size = size;
        table.assign(size + 1, 0);
    }
    void add(int l, int r, T x) {
        for (; l <= size; l += l & -l) {
            table[l] += x;
        }
        for (++r; r <= size; r += r & -r) {
            table[r] -= x;
        }
    }
    T get(int i) {
        T sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += table[i];
        }
        return sum;
    }
};
