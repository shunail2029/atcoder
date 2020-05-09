#include <algorithm>
#include <vector>

// LCS (Longest Common Subsequence) 最長共通部分列
template<class T>
long long lcs(const std::vector<T> &v1, const std::vector<T> &v2) {
    int l1 = (int)v1.size(), l2 = (int)v2.size();
    std::vector<std::vector<long long>> dp(l1, std::vector<long long>(l2, 0LL));

    for (int i=0; i<l1; ++i) {
        for (int j=0; j<l2; ++j) {
            if (v1.at(l1) == v2.at(l2)) {
                dp.at(i+1).at(j+1) = dp.at(i).at(j);
            } else {
                dp.at(i+1).at(j+1) = std::max(dp.at(i+1).at(j), dp.at(i).at(j+1));
            }
        }
    }

    return dp.at(l1).at(l2);
}
