#include <cassert>
#include <vector>

// Chinese Remainder Theorem (CRT) 中国余剰定理
// returns (r, m) s.t. x = r (mod m)
// if no solution, returns (0, 1)
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long d = extGCD(b, a%b, y, x);
    y -= a / b * x;
    return d;
}

std::pair<long long, long long> CRT(const std::vector<long long> &r, const std::vector<long long> &m) {
    if (r.empty() && m.empty()) return std::make_pair(0, 1);
    assert(r.size() == m.size());

    long long res = 0, mod = 1;
    for (int i=0; i<(int)r.size(); ++i) {
        long long p, q, cr = r[i], cm = m[i];
        if (mod < cm) std::swap(res, cr), std::swap(mod, cm);
        long long d = extGCD(mod, cm, p, q);
        if ((cr - res) % d != 0) return std::make_pair(0, -1);
        long long u = cm / d;
        res += (cr - res) / d % u * p % u * mod;
        mod *= u;
        if (res < 0) res += mod;
    }
    return std::make_pair(res, mod);
}

// Garner's algorithm
// m[i], m[j] must be coprime, for all i, j
long long Garner(const std::vector<long long> &r, const std::vector<long long> &m, long long mod) {
    assert(r.size() == m.size());

    auto inv = [](long long n, long long mod) -> long long {
        long long res = 1;
        while (n > 1) {
            (res *= (mod - mod / n)) %= mod;
            n = mod % n;
        }
        return res;
    };

    int len = (int)m.size() + 1;
    std::vector<long long> res(len, 0), mps(len, 1);
    for (int i=0; i<(int)r.size(); ++i) {
        long long t = r[i] - res[i];
        if (t < 0) t += m[i];
        (t *= inv(mps[i], m[i])) %= m[i];
        for (int j=i+1; j<len; ++j) {
            long long tm = j < len-1 ? m[j] : mod;
            (res[j] += t * mps[i]) %= tm;
            (mps[j] *= m[i]) %= tm;
        }
    }
    return res.back();
}
