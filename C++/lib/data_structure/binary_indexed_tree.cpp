#include <vector>

// Binary Indexed Tree (BIT)
template<class T>
class BinaryIndexedTree {
    private:
        int N;
        std::vector<T> dat;
    public:
        BinaryIndexedTree(int n) : N(n), dat(n+1, static_cast<T>(0)) {}
        // a is 1-indexed
        void add(int a, const T v) {
            while (a <= N) {
                dat.at(a) += v;
                a += (a & -a);
            }
        }
        // return sum of [1, a]
        // a is 1-indexed
        T sum(int a) {
            T res = static_cast<T>(0);
            while (a > 0) {
                res += dat.at(a);
                a -= (a & -a);
            }
            return res;
        }
        // return sum of [a. b)
        // a and b are 1-indexed
        T sum(int a, int b) {
            return sum(b-1) - sum(a-1);
        }
};
