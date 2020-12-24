#include <algorithm>

// greatest common divisor 最大公約数
long long gcd(long long a, long long b) {
    if (a < b) std::swap(a, b);
    if (b == 0) return a;

    while (b > 0) {
        long long tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}

// extra GCD 拡張ユークリッドの互除法
/* ax + by = gcd(a, b) の解をx,yに格納する
   return value : gcd(a, b) */
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long d = extGCD(b, a%b, y, x);
    y -= a / b * x;
    return d;
}

// least common multiple 最小公倍数
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}
