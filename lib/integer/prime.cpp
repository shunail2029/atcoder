#include <map>
#include <vector>

// prime judge 素数判定
bool isPrime(long long n) {
    if (n == 1) return false;

    for (long long i=2; i*i<=n; i++) {
        if (n%i == 0) return false;
    }
    return true;
}

// devisor enumeration 約数列挙
std::vector<long long> divEnu(long long n) {
    std::vector<long long> res;
    for (long long i=1; i*i<=n; i++) {
        if (n%i == 0) {
            res.push_back(i);
            if (n/i != i) res.push_back(n/i);
        }
    }
    return res;
}

// prime factorization 素因数分解
std::map<long long, int> primeFact(long long n) {
    std::map<long long, int> res;
    for (long long i=2; i*i<=n; i++) {
        while (n%i == 0) {
            res[i]++;
            n /= i;
        }
    }
    if (n != 1) res[n] = 1;
    return res;
}

// prime enumeration 素数列挙
std::vector<long long> primeEnu(long long n) {
    std::vector<long long> res;
    std::vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (long long i=2; i<=n; i++) {
        if (is_prime[i]) {
            res.push_back(i);
            for (long long j=2*i; j<=n; j+=i) is_prime[j] = false;
        }
    }
    return res;
}
