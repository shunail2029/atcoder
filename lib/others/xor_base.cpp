#include <vector>

// Xor Base
class XorBase {
    private:
        std::vector<long long> base;
    public:
        XorBase() {}
        void add(long long x) {
            for (long long b : base) {
                if ((x ^ b) < x) {
                    x ^= b;
                }
            }
            if (x != 0) base.push_back(x);
        }
        bool check(long long x) const {
            for (long long b : base) {
                if ((x ^ b) < x) {
                    x ^= b;
                }
            }
            if (x == 0) return true;
            else return false;
        }
};
