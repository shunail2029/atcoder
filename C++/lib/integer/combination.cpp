// combination 組み合わせ数
long long comb(long long n, long long r) {
    long long r_buf = (r <= n/2) ? r : n-r;
    if (r_buf == 0) return 1;
    else return (n-r_buf+1) * comb(n, r_buf-1) / r_buf;
}

// combination_mod 余りでいい時の組み合わせ数
#define mod 1000000007

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
    long long deno = 1;
    long long mole = 1;
    long long r_buf = (r <= n/2) ? r : n-r;
    for (int i=1; i<=r_buf; i++) {
        mole *= i % mod;
        mole %= mod;
    }
    for (int i=n-r_buf+1; i<=n; i++) {
        deno *= i % mod;
        deno %= mod;
    }
    mole = inv(mole);
    return (mole * deno) % mod;
}
