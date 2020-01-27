#include <utility>

constexpr int MOD = 1e9 + 7;

// modular multiplicative inverse モジュラ逆数
/* return value : 1/n (MOD ~)
   n < MOD を想定
   note : (MOD - MOD / n)
            ↑ このmodは正にするためであって特に本質的でない
          res = res * (-MOD / n) でも問題ないが， res < 0 となることがあるので注意 */
long long inv(long long n) {
    long long res = 1;
    while (n > 1) {
        res *= (MOD - MOD / n);
        res %= MOD;
        n = MOD % n;
    }
    return res;
}

long long inv2(long long n) {
    long long a = n, b = MOD, u = 1, v = 0;
    while (b > 0) {
        long long tmp = a / b;
        a -= tmp * b; std::swap(a, b);
        u -= tmp * v; std::swap(u, v);
    }
    return u;
}
