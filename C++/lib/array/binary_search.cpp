#include <cmath>
#include <vector>

// binary_search 二分探索
template<class T>
long long binary_searching(const std::vector<T> &str, const T &key, long long imin, long long imax) {
    int ok = (int)str.size();
    int ng = -1;
    while (abs(ok-ng) > 1) {
        int mid = (ok+ng)/2;
        if (str.at(mid) >= key) ok = mid;
        else ng = mid;
    }
    return ok;
}
