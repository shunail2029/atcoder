#include <string>
#include <vector>

class RollingHash {
    private:
        static const int base1 = 10007, base2 = 10009;
        static const int mod1 = 1000000007, mod2 = 1000000009;
        std::vector<long long> hash1, hash2, pow1, pow2;
    public:
        const int N;
        RollingHash(const std::string &S) : N((int)S.size()) {
            hash1.resize(N+1);
            hash2.resize(N+1);
            pow1.resize(N+1);
            pow2.resize(N+1);
            hash1[0] = hash2[0] = 0;
            pow1[0] = pow2[0] = 1;
            for (int i=1; i<N+1; i++) {
                hash1[i] = (hash1[i-1] * base1 + S[i-1]) % mod1;
                hash2[i] = (hash2[i-1] * base2 + S[i-1]) % mod2;
                pow1[i] = (pow1[i-1] * base1) % mod1;
                pow2[i] = (pow2[i-1] * base2) % mod2;
            }
        }
        std::pair<long long, long long> get(int l, int r) const {
            long long res1 = (hash1[r] - hash1[l] * pow1[r-l]) % mod1;
            if (res1 < 0) res1 += mod1;
            long long res2 = (hash2[r] - hash2[l] * pow2[r-l]) % mod2;
            if (res2 < 0) res2 += mod2;
            return std::make_pair(res1, res2);
        }
        int getLCP(int a, int b) const {
            int len = std::min(N - a, N - b);
            int ok = 0, ng = len+1;
            while (abs(ok - ng) > 1) {
                int mid = (ok + ng) / 2;
                if (get(a, a+mid) == get(b, b+mid)) ok = mid;
                else ng = mid;
            }
            return ok;
        }
        int getLCP(const RollingHash &T, int a, int b) const {
            int len = std::min(N - a, T.N - b);
            int ok = 0, ng = len+1;
            while (abs(ok - ng) > 1) {
                int mid = (ok + ng) / 2;
                if (get(a, a+mid) == T.get(b, b+mid)) ok = mid;
                else ng = mid;
            }
            return ok;
        }
};
