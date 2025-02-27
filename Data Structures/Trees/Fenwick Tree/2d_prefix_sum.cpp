template<typename T>
struct FenwickTree2D {
    vector<vector<T>> table;
    int height, width;
    FenwickTree2D(int height = 0, int width = 0) {
        this->height = height;
        this->width = width;
        table.assign(height + 1, vector<T>(width + 1));
    }
    void add(int i, int j, T x) {
        for (; i <= height; i += i & -i) {
            for (int y = j; y <= width; y += y & -y) {
                table[i][y] += x;
            }
        }
    }
    T get(int i, int j) {
        T sum = 0;
        for (; i > 0; i -= i & -i) {
            for (int y = j; y > 0; y -= y & -y) {
                sum += table[i][y];
            }
        }
        return sum;
    }
    T get(int i1, int j1, int i2, int j2) {
        return get(i2, j2) - get(i2, j1 - 1) - get(i1 - 1, j2) + get(i1 - 1, j1 - 1);
    }
};