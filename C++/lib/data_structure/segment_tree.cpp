#include <functional>
#include <vector>

// Segmant Tree セグメント木
template<class T>
class SegmentTree {
    using Func = std::function<T(T, T)>;
    private:
        const Func F;
        const T DEF;
        int N;
        std::vector<T> dat;
    public:
        SegmentTree(int n, const Func f, const T def) : F(f), DEF(def) {
            N = 1;
            while (N < n) N *= 2;
            dat.assign(2*N, DEF);
        }
        // a is 0-indexed
        void set(int a, const T v) {
            dat.at(a+N) = v;
        }
        void build() {
            for (int i=N-1; i>0; --i) dat.at(i) = F(dat.at(2*i), dat.at(2*i+1));
        }
        // a is 0-indexed
        void update(int a, const T v) {
            int cur = a + N;
            dat.at(cur) = v;
            while ((cur /= 2) > 0) dat.at(cur) = F(dat.at(2*cur), dat.at(2*cur+1));
        }
        // return value of [a, b)
        // a and b are 0-indexed
        T get(int a, int b) {
            return get(a, b, 1, 0, N);
        }
        T get(int a, int b, int k, int l, int r) {
            if (b <= l || r <= a) return DEF;
            if (a <= l && r <= b) return dat.at(k);
            T vleft = get(a, b, 2*k, l, (l+r)/2);
            T vright = get(a, b, 2*k+1, (l+r)/2, r);
            return F(vleft, vright);
        }
        // a is 0-indexed
        T at(int a) { return dat.at(a+N); }
};


// Segmant Tree セグメント木
template<class T>
class _SegmentTree {
    using Func = std::function<T(T, T)>;
    private:
        const Func F;
        const T DEF;
        int N;
        std::vector<T> dat;
    public:
        SegmentTree(int n, const Func f, const T def) : F(f), DEF(def) {
            N = 1;
            while (N < n) N *= 2;
            dat.assign(2*N, DEF);
        }
        void set(int a, const T v) {
            dat.at(a+N) = v;
        }
        void build() {
            for (int i=N-1; i>0; --i) dat.at(i) = F(dat.at(2*i), dat.at(2*i+1));
        }
        void update(int a, const T v) {
            int cur = a + N;
            dat.at(cur) = v;
            while (cur >>= 1) dat.at(cur) = F(dat.at(2*cur), dat.at(2*cur+1));
        }
        T get(int a, int b) {
            T vleft = DEF, vright = DEF;
            for (int left=a+N, right=b+N; left<right; left>>=1, right>>=1) {
                if (left & 1) vleft = F(vleft, dat.at(left++));
                if (right & 1) vright = F(vright, dat.at(--right));
            }
            return F(vleft, vright);
        }
        T at(int a) { return dat.at(a+N); }
};
