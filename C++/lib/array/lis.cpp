#include <algorithm>
#include <vector>

// LIS(Longest Increasing Subsequence) 最長増加部分列
int lis(const std::vector<long long> &vec) {
    int len = (int)vec.size();
    std::vector<long long> dp(len, 1e16);
    for (int i=0; i<len; i++) {
        long long tmp = vec.at(i);
        auto iter = std::lower_bound(dp.begin(), dp.end(), tmp);
        *iter = tmp;
    }
    return std::lower_bound(dp.begin(), dp.end(), 1e16) - dp.begin();
}
