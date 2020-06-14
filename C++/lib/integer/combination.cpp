// combination 組み合わせ数
long long comb(long long n, long long r) {
    r = (r <= n/2) ? r : n-r;
    if (r < 0) return 0;
    if (r == 0) return 1;
    else return (n-r+1) * comb(n, r-1) / r;
}

// combination_mod 余りでいい時の組み合わせ数
constexpr int MOD = 1e9 + 7;

long long inv(long long n) {
    long long res = 1;
    while (n > 1) {
        res *= (MOD - MOD/n);
        res %= MOD;
        n = MOD % n;
    }
    return res;
}

long long comb_mod(long long n, long long r) {
    r = (r <= n/2) ? r : n-r;
    long long nume = 1;
    long long deno = 1;
    if (r < 0) return 0;
    if (r == 0) return 1;

    for (long long i=1; i<=r; i++) {
        deno *= i % MOD;
        deno %= MOD;
    }
    for (long long i=n-r+1; i<=n; i++) {
        nume *= i % MOD;
        nume %= MOD;
    }
    deno = inv(deno);
    return (deno * nume) % MOD;
}
