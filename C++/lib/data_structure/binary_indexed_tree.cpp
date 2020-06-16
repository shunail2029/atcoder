#include <functional>
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
                dat[a] += v;
                a += (a & -a);
            }
        }
        // return sum of [1, a]
        // a is 1-indexed
        T sum(int a) const {
            T res = static_cast<T>(0);
            while (a > 0) {
                res += dat[a];
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
            for (int i=1; i<n+1; ++i) ind[i] = i;
        }
        // return index of max of [l, r]
        // l and r are 1-indexed
        int queryInd(int l, int r) const {
            int res = 0;
            while (l <= r) {
                if (r-(r&-r)+1 >= l) {
                    if (dat[ind[r]] > dat[res]) res = ind[r];
                    r -= (r & -r);
                } else {
                    if (dat[r] > dat[res]) res = r;
                    --r;
                }
            }
            return res;
        }
        // return max of [l, r]
        // l and r are 1-indexed
        T query(int l, int r) const { return dat[queryInd(l, r)]; }
        // a is 1-indexed
        void update(int a, const T v) {
            dat[a] = v;
            int cur = a;
            while (cur <= N) {
                if (ind[cur] == a) {
                    int nx = queryInd(cur-(cur&-cur)+1, cur-1);
                    ind[cur] = dat[cur] > dat[nx] ? cur : nx;
                } else {
                    if (dat[a] > dat[ind[cur]]) ind[cur] = a;
                }
                cur += (cur & -cur);
            }
        }
        // return value of a
        T at(int a) const { return dat.at(a); }
};

// Binary Indexed Tree (BIT)
template<class T>
class _BinaryIndexedTree {
    using Func = std::function<T(T, T)>;
    private:
        const Func F;
        const T DEF;
        int N;
        std::vector<T> dat, val;
    public:
        _BinaryIndexedTree(int n, const Func f, T def) : F(f), DEF(def), N(n), dat(n+1, def), val(n+1, def) {}
        // return value of [l, r]
        // l and r are 1-indexed
        T query(int l, int r) const {
            T res = DEF;
            while (l <= r) {
                if (r-(r&-r)+1 >= l) {
                    res = F(val[r], res);
                    r -= (r & -r);
                } else {
                    res = F(dat[r], res);
                    --r;
                }
            }
            return res;
        }
        // a is 1-indexed
        void update(int a, const T v) {
            dat[a] = v;
            int cur = a;
            while (cur <= N) {
                T nx = query(cur-(cur&-cur)+1, cur-1);
                val[cur] = F(nx, dat[cur]);
                cur += (cur & -cur);
            }
        }
        // return value of a
        T at(int a) const { return dat.at(a); }
};
