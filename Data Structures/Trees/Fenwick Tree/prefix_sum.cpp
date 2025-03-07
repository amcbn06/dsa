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
    T get(int i) {
        T sum = 0;
        for (; i > 0; i -= i & -i) {
            sum += table[i];
        }
        return sum;
    }
    T get(int i, int j) {
        return get(j) - get(i - 1);
    }
};
