#include <utility>
#include <iostream>

template<int mod>
class ModInt {
    private:
        long long val;
    public:
        constexpr ModInt(const long long v = 0) : val(v%mod) { if (val < 0) val += mod; }
        constexpr ModInt(const ModInt &v) : val(v.val) {}
        constexpr ModInt &operator=(const long long v) { val = v; return *this; }
        constexpr ModInt &operator=(const ModInt &v) { if (this != &v) val = v.val; return *this; }
        constexpr ModInt operator+() const { return ModInt(val); }
        constexpr ModInt operator-() const { return ModInt(-val); }
        constexpr ModInt operator+(const ModInt &v) const { return ModInt(*this) += v; }
        constexpr ModInt operator-(const ModInt &v) const { return ModInt(*this) -= v; }
        constexpr ModInt operator*(const ModInt &v) const { return ModInt(*this) *= v; }
        constexpr ModInt operator/(const ModInt &v) const { return ModInt(*this) /= v; }
        constexpr ModInt &operator+=(const ModInt &v) { val += v.val; if (val >= mod) val -= mod; return *this; }
        constexpr ModInt &operator-=(const ModInt &v) { val -= v.val; if (val < 0) val += mod; return *this; }
        constexpr ModInt &operator*=(const ModInt &v) { val *= v.val; if (val >= mod) val %= mod; return *this; }
        constexpr ModInt &operator/=(const ModInt &v) { val *= v.inverse(); if (val >= mod) val %= mod; return *this; }
        constexpr ModInt &operator++() { ++val; if (val >= mod) val -= mod; return *this; }
        constexpr ModInt &operator--() { --val; if (val < 0) val += mod; return *this; }
        constexpr ModInt operator++(int) { ModInt tmp(*this); operator++(); return tmp; }
        constexpr ModInt operator--(int) { ModInt tmp(*this); operator--(); return tmp; }
        constexpr bool operator==(const ModInt &v) const { return val == v.val; }
        constexpr bool operator!=(const ModInt &v) const { return !(*this == v); }
        friend std::istream &operator>>(std::istream &s, ModInt &v) { long long tmp; s >> tmp; v = ModInt(tmp); return s; }
        friend std::ostream &operator<<(std::ostream &s, const ModInt &v) { return s << v.val; }
        constexpr ModInt inverse() const {
            long long n = val, res = 1;
            while (n > 1) {
                res *= (mod - mod / n);
                res %= mod;
                n = mod % n;
            }
            return ModInt(res);
        }
        friend constexpr ModInt modpow(ModInt v, long long n) {
            ModInt res(1);
            for ( ; n>0; n>>=1) {
                if (n & 1) res *= v;
                v *= v;
            }
            return res;
        }
};
