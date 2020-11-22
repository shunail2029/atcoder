// combination 組み合わせ数
long long comb(long long n, long long r) {
    r = (r <= n/2) ? r : n-r;
    if (r < 0) return 0;
    if (r == 0) return 1;
    else return (n-r+1) * comb(n, r-1) / r;
}

// combination_mod 余りでいい時の組み合わせ数
long long inv(long long n, long long mod) {
    long long res = 1;
    while (n > 1) {
        (res *= (mod - mod / n)) %= mod;
        n = mod % n;
    }
    return res;
}

long long comb_mod(long long n, long long r, long long mod) {
    r = (r <= n/2) ? r : n-r;
    if (r < 0) return 0;
    if (r == 0) return 1;

    long long nume = 1, deno = 1;
    for (long long i=1; i<=r; i++) {
        deno *= i % mod;
        deno %= mod;
    }
    for (long long i=n-r+1; i<=n; i++) {
        nume *= i % mod;
        nume %= mod;
    }
    deno = inv(deno, mod);
    return (deno * nume) % mod;
}
