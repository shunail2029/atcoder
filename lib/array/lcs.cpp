#include <algorithm>
#include <vector>

// LCS (Longest Common Subsequence) 最長共通部分列
template<class T>
int lcs(const std::vector<T> &v1, const std::vector<T> &v2) {
    int l1 = (int)v1.size(), l2 = (int)v2.size();
    std::vector<std::vector<int>> dp(l1, std::vector<int>(l2, 0));

    for (int i=0; i<l1; ++i) {
        for (int j=0; j<l2; ++j) {
            if (v1[i] == v2[j]) dp[i+1][j+1] = dp[i][j] + 1;
            else dp[i+1][j+1] = std::max(dp[i+1][j], dp[i][j+1]);
        }
    }
    return dp[l1][l2];
}
