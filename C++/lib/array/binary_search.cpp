#include <cmath>
#include <vector>

template<typename T>
bool isOK(std::vector<T> &str, T key, int index) {
    if (str.at(index) >= key) return true;
    else return false;
}

// binary_search 二分探索
template<typename T>
long long binary_searching(std::vector<T> &str, T key, long long imin, long long imax) {
    int ok = (int)str.size();
    int ng = -1;
    while (abs(ok-ng) > 1) {
        int mid = (ok+ng)/2;
        if (isOK(str, key, mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}
