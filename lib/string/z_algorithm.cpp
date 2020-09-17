#include <algorithm>
#include <string>
#include <vector>

// z-algorithm
std::vector<int> Zalgorithm(const std::string& s) {
    int n = (int)s.size();
    if (n == 0) return {};

    std::vector<int> z(n);
    z[0] = 0;
    for (int i=1, j=0; i<n; ++i) {
        if (i + z[i-j] < j + z[j]) {
            z[i] = z[i-j];
        } else {
            int k = std::max(0, j + z[j] - i);
            while (i + k < n && s[i+k] == s[k]) ++k;
            z[i] = k;
            j = i;
        }
    }
    z[0] = n;

    return z;
}
