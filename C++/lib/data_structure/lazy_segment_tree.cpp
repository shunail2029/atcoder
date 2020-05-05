#include <algorithm>
#include <limits>
#include <vector>

// Starry Sky Tree (区間加算・区間最小)
template<class T>
class StarrySkyTree {
    private:
        int N;
        const T MAX;
        const T ZERO;
        std::vector<T> dat, lazy;
    public:
        StarrySkyTree(int n) : MAX(std::numeric_limits<T>::max()), ZERO(static_cast<T>(0)) {
            N = 1;
            while (N < n) N *= 2;
            dat.assign(2*N, MAX);
            lazy.assign(2*N, ZERO);
        }
        // a is 0-indexed
        void set(int a, const T v) {
            dat.at(a+N) = v;
        }
        void build() {
            for (int i=N-1; i>0; --i) dat.at(i) = std::min(dat.at(2*i), dat.at(2*i+1));
        }
        void eval(int k, int l, int r) {
            if (lazy.at(k) == ZERO) return;

            dat.at(k) += lazy.at(k);
            if (r - l > 1) {
                lazy.at(2*k) += lazy.at(k);
                lazy.at(2*k+1) += lazy.at(k);
            }
            lazy.at(k) = ZERO;
        }
        // add v to [a, b)
        // a and b are 0-indexed
        void add(int a, int b, const T v) {
            return add (a, b, v, 1, 0, N);
        }
        void add(int a, int b, const T v, int k, int l, int r) {
            eval(k, l, r);

            if (b <= l || r <= a) return;
            if (a <= l && r <= b) {
                lazy.at(k) += v;
                eval(k, l, r);
            } else {
                add(a, b, v, 2*k, l, (l+r)/2);
                add(a, b, v, 2*k+1, (l+r)/2, r);
                dat.at(k) = std::min(dat.at(2*k), dat.at(2*k+1));
            }
        }
        // get min of [a, b)
        // a and b are 0-indexed
        T get(int a, int b) {
            return get(a, b, 1, 0, N);
        }
        T get(int a, int b, int k, int l, int r) {
            eval(k, l, r);

            if (b <= l || r <= a) return MAX;
            if (a <= l && r <= b) return dat.at(k);
            T vleft = get(a, b, 2*k, l, (l+r)/2);
            T vright = get(a, b, 2*k+1, (l+r)/2, r);
            return std::min(vleft, vright);
        }
};
