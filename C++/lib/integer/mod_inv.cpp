constexpr long long MOD = 1e9 + 7;

// modular multiplicative inverse モジュラ逆数
/* return value : 1/n (MOD ~)
   n < MOD を想定
   note : (MOD - MOD / n)
            ↑ このmodは正にするためであって特に本質的でない
          ans = ans * (-MOD / n) でも問題ないが，ans < 0 となることがあるので注意 */
long long inv(long long n) {
    long long res = 1;
    while (n > 1) {
        res *= (MOD - MOD / n);
        res %= MOD;
        n = MOD % n;
    }
    return res;
}
