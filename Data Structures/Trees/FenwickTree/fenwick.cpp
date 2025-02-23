// Works with indicies in range [1, size]
template<typename T>
struct FenwickTree {
    vector<T> table;
    int size;
    FenwickTree(int size = 0) {
        this->size = size;
        table.assign(size + 1, 0);
    }
    void add(int i, T x) {
        for (; i <= size; i += i & -i) {
            table[i] += x;
        }
    }
    T query(int i) {
        T sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += table[i];
        }
        return sum;
    }
    T query(int i, int j) {
        return query(j) - query(i - 1);
    }
};
