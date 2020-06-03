#include <limits>
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
        T sum(int a) const {
            T res = static_cast<T>(0);
            while (a > 0) {
                res += dat.at(a);
                a -= (a & -a);
            }
            return res;
        }
        // return sum of [a. b)
        // a and b are 1-indexed
        T sum(int a, int b) const {
            return sum(b-1) - sum(a-1);
        }
};

// Binary Indexed Tree RMQ (BIT)
template<class T>
class BinaryIndexedTreeRMQ {
    private:
        int N;
        std::vector<T> dat, ind;
    public:
        BinaryIndexedTreeRMQ(int n, T def) : N(n), dat(n+1, def), ind(n+1) {
            for (int i=1; i<n+1; ++i) ind.at(i) = i;
        }
        // return index of max of [l, r]
        // l and r are 1-indexed
        int queryInd(int l, int r) const {
            int res = 0;
            while (l <= r) {
                if (r-(r&-r)+1 >= l) {
                    if (dat.at(ind.at(r)) > dat.at(res)) res = ind.at(r);
                    r -= (r & -r);
                } else {
                    if (dat.at(r) > dat.at(res)) res = r;
                    --r;
                }
            }
            return res;
        }
        // return max of [l, r]
        // l and r are 1-indexed
        T query(int l, int r) const {
            return dat.at(queryInd(l, r));
        }
        // a is 1-indexed
        void update(int a, const T v) {
            dat.at(a) = v;
            int cur = a;
            while (cur <= N) {
                if (ind.at(cur) == a) {
                    int nx = queryInd(cur-(cur&-cur)+1, cur-1);
                    ind.at(cur) = dat.at(cur) > dat.at(nx) ? cur : nx;
                } else {
                    if (dat.at(a) > dat.at(ind.at(cur))) ind.at(cur) = a;
                }
                cur += (cur & -cur);
            }
        }
        // return value of a
        T at(int a) const {
            return dat.at(a);
        }
};
