template <typename T>
struct Matrix {
    int r, c;
    vector<vector<T>> mat;
 
    Matrix(int r, int c) : r(r), c(c), mat(r, vector<T>(c)) {}
    
    Matrix(const vector<vector<T>>& v) : mat(v) {
        r = v.size();
        c = r ? v[0].size() : 0;
    }
 
    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; ++i) {
            res.mat[i][i] = 1;
        }
        return res;
    }
 
    vector<T>& operator[](int i) { return mat[i]; }
    const vector<T>& operator[](int i) const { return mat[i]; }
 
    Matrix operator*(const Matrix& rhs) const {
        assert(c == rhs.r);
        Matrix res(r, rhs.c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < rhs.c; ++j) {
                for (int k = 0; k < c; ++k) {
                    res[i][j] += mat[i][k] * rhs[k][j];
                }
            }
        }
        return res;
    }
 
    Matrix& operator*=(const Matrix& rhs) {
        return *this = *this * rhs;
    }
 
    Matrix operator+(const Matrix& rhs) const {
        assert(r == rhs.r && c == rhs.c);
        Matrix res(r, c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                res[i][j] = mat[i][j] + rhs[i][j];
            }
        }
        return res;
    }
 
    Matrix& operator+=(const Matrix& rhs) {
        assert(r == rhs.r && c == rhs.c);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                mat[i][j] += rhs[i][j];
            }
        }
        return *this;
    }
 
    Matrix pow(long long p) const {
        assert(r == c);
        Matrix res = identity(r);
        Matrix a = *this;
        for (; p > 0; p >>= 1) {
            if (p & 1) res *= a;
            a *= a;
        }
        return res;
    }
 
    friend ostream& operator<<(ostream& os, const Matrix& m) {
        for (int i = 0; i < m.r; ++i) {
            for (int j = 0; j < m.c; ++j) {
                os << m[i][j] << " \n"[j == m.c - 1];
            }
        }
        return os;
    }
};
