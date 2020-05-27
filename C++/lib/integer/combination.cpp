// combination 組み合わせ数
long long comb(long long n, long long r) {
    long long r_new = (r <= n/2) ? r : n-r;
    if (r_new < 0) return 0;
    if (r_new == 0) return 1;
    else return (n-r_new+1) * comb(n, r_new-1) / r_new;
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
    long long nume = 1;
    long long deno = 1;
    long long r_new = (r <= n/2) ? r : n-r;
    if (r_new < 0) {
        return 0;
    } else if (r_new == 0) {
        return 1;
    }

    for (long long i=1; i<=r_new; i++) {
        deno *= i % MOD;
        deno %= MOD;
    }
    for (long long i=n-r_new+1; i<=n; i++) {
        nume *= i % MOD;
        nume %= MOD;
    }
    deno = inv(deno);
    return (deno * nume) % MOD;
}
