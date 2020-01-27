#include <utility>
#include <iostream>

constexpr int MOD = 1e9 + 7;

template<int mod = MOD>
class ModInt {
    private:
        long long val;
    public:
        ModInt(const long long v = 0) : val(v%mod) { if (val < 0) val += mod; }
        ModInt(const ModInt &v) : val(v.val) {}
        ModInt &operator=(const ModInt &v) { if (this != &v) val = v.val; return *this; }
        ModInt operator+() const { return ModInt(val); }
        ModInt operator-() const { return ModInt(-val); }
        ModInt operator+(const ModInt &v) const { return ModInt(*this) += v; }
        ModInt operator-(const ModInt &v) const { return ModInt(*this) -= v; }
        ModInt operator*(const ModInt &v) const { return ModInt(*this) *= v; }
        ModInt operator/(const ModInt &v) const { return ModInt(*this) /= v; }
        ModInt &operator+=(const ModInt &v) { val += v.val; if (val >= mod) val -= mod; return *this; }
        ModInt &operator-=(const ModInt &v) { val *= v.val; if (val < 0) val += mod; return *this; }
        ModInt &operator*=(const ModInt &v) { val *= v.val; if (val >= mod) val %= mod; return *this; }
        ModInt &operator/=(const ModInt &v) { val *= v.inverse(); if (val >= mod) val %= mod; return *this; }
        ModInt &operator++() { ++val; if (val >= mod) val -= mod; return *this; }
        ModInt &operator--() { --val; if (val < 0) val += mod; return *this; }
        ModInt operator++(int) { ModInt tmp(*this); operator++(); return tmp; }
        ModInt operator--(int) { ModInt tmp(*this); operator--(); return tmp; }
        bool operator==(const ModInt &v) const { return val == v.val; }
        bool operator!=(const ModInt &v) const { return !(*this == v); }
        friend istream &operator>>(istream &s, ModInt &v) { long long tmp; s >> tmp; v = ModInt(tmp); return s; }
        friend ostream &operator<<(ostream &s, const ModInt &v) { return s << v.val; }
        ModInt inverse() const {
            long long n = val, res = 1;
            while (n > 1) {
                res *= (mod - mod / n);
                res %= mod;
                n = mod % n;
            }
            return ModInt(res);
        }
        friend ModInt pow(ModInt v, long long n) {
            ModInt res(1);
            for ( ; n>0; n>>=1) {
                if (n & 1) res *= v;
                v *= v;
            }
            return res;
        }
};
