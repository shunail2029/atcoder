#include <cassert>
#include <vector>

template<class T>
class Matrix {
    private:
        int row, col;
        std::vector<std::vector<T>> val;
    public:
        Matrix(int row, int col) : row(row), col(col), val(row, std::vector<T>(col)) {}
        Matrix(const Matrix &A) : row(A.row), col(A.col), val(A.val) {}
        Matrix &operator=(const Matrix &A) {
            row = A.row;
            col = A.col;
            val = A.val;
            return *this;
        }
        Matrix operator+(const Matrix &A) const { return Matrix(*this) += A; }
        Matrix operator-(const Matrix &A) const { return Matrix(*this) -= A; }
        Matrix operator*(const Matrix &A) const { return Matrix(*this) *= A; }
        Matrix &operator+=(const Matrix &A) {
            if (row != A.row || col != A.col) assert(false);
            for (int i=0; i<row; ++i) {
                for (int j=0; j<col; ++j) {
                    val[i][j] += A[i][j];
                }
            }
            return *this;
        }
        Matrix &operator-=(const Matrix &A) {
            if (row != A.row || col != A.col) assert(false);
            for (int i=0; i<row; ++i) {
                for (int j=0; j<col; ++j) {
                    val[i][j] -= A[i][j];
                }
            }
            return *this;
        }
        Matrix &operator*=(const Matrix &A) {
            if (col != A.row) assert(false);
            Matrix R(row, A.col);
            for (int i=0; i<row; ++i) {
                for (int j=0; j<A.col; ++j) {
                    for (int k=0; k<col; ++k) {
                        R[i][j] += val[i][k] * A[k][j];
                    }
                }
            }
            return *this = R;
        }
        std::vector<T> &operator[](int i) { return val[i]; }
        const std::vector<T> &operator[](int i) const { return val[i]; }
        void resize(int r, int c) {
            row = r;
            col = c;
            val.resize(row);
            for (int i=0; i<row; ++i) val[i].resize(col);
        }
        static Matrix E(int n) {
            Matrix R(n, n);
            for (int i=0; i<n; ++i) R[i][i] = 1;
            return R;
        }
        static Matrix pow(Matrix A, long long n) {
            if (A.row != A.col) assert(false);
            Matrix R(E(A.row));
            for ( ; n>0; n>>=1) {
                if (n & 1) R *= A;
                A *= A;
            }
            return R;
        }
};
