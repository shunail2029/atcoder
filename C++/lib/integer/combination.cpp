// combination 組み合わせ数
long long comb(long long n, long long r) {
    long long r_buf = (r <= n/2) ? r : n-r;
    if (r_buf == 0) return 1;
    else return (n-r_buf+1) * comb(n, r_buf-1) / r_buf;
}

// combination_mod 余りでいい時の組み合わせ数
constexpr long long mod = 1000000007;

long long inv(long long n) {
    long long res = 1;
    while (n > 1) {
        res *= (mod - mod/n);
        res %= mod;
        n = mod % n;
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
        deno *= i % mod;
        deno %= mod;
    }
    for (long long i=n-r_new+1; i<=n; i++) {
        nume *= i % mod;
        nume %= mod;
    }
    deno = inv(deno);
    return (deno * nume) % mod;
}
