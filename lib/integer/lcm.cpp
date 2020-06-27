#include "../integer/gcd.cpp"

// least common multiple 最小公倍数
long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}
