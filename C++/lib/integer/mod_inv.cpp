#define mod 1000000007

// modular multiplicative inverse モジュラ逆数
/* return value : 1/n (mod ~)
   n < mod を想定
   note : (mod - mod / n)
            ↑ このmodは正にするためであって特に本質的でない
          ans = ans * (-mod / n) でも問題ないが，ans < 0 となることがあるので注意 */
long long inv(long long n) {
    long long res = 1;
    while (n > 1) {
        res *= (mod - mod / n);
        res %= mod;
        n = mod % n;
    }
    return res;
}
