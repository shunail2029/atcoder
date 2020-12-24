#include <cmath>
#include <vector>

// binary_search 二分探索
template<class T>
long long binarySearching(const std::vector<T> &vec, const T key) {
    int ok = (int)vec.size(), ng = -1;
    while (abs(ok - ng) > 1) {
        int mid = (ok + ng) / 2;
        if (vec[mid] >= key) ok = mid;
        else ng = mid;
    }
    return ok;
}
