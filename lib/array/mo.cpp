#include <algorithm>
#include <cmath>
#include <numeric>
#include <vector>

// Mo's algorithm
class Mo {
    private:
        int width;
        std::vector<int> left, right, order;
        std::vector<bool> v;
    public:
        Mo(int N, int Q) : width((int)sqrt(N)), order(Q), v(N) {
            std::iota(order.begin(), order.end(), 0);
        }
        // insert query [l, r)
        void insert(int l, int r) {
            left.push_back(l);
            right.push_back(r);
        }
        void run() {
            std::sort(order.begin(), order.end(), [&](int a, int b) {
                int ablock = left[a] / width, bblock = left[b] / width;
                if (ablock != bblock) return ablock < bblock;
                if (ablock & 1) return right[a] > right[b];
                return right[a] < right[b];
            });
            int nl = 0, nr = 0;
            for (int idx : order) {
                while (nl > left[idx]) push(--nl);
                while (nr < right[idx]) push(nr++);
                while (nl < left[idx]) push(nl++);
                while (nr > right[idx]) push(--nr);
                rem(idx);
            }
        }
        void push(int idx) {
            v[idx].flip();
            if (v[idx]) add(idx);
            else del(idx);
        }
        // need to be implemented
        void add(int idx);
        void del(int idx);
        void rem(int idx);
};
