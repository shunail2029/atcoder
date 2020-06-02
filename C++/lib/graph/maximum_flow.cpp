#include <algorithm>
#include <queue>
#include <vector>

using WGraph = std::vector<std::vector<std::pair<int, long long>>>;
constexpr long long LINF = 1e18;

// Edmonds-Karp algorithm
long long edmondsKarp(const WGraph &G, const int s, const int t) {
    int n = (int)G.size();
    std::vector<std::vector<long long>> cap(n, std::vector<long long>(n));
    for (int i=0; i<n; ++i) {
        for (auto p : G.at(i)) {
            cap.at(i).at(p.first) = p.second;
        }
    }

    long long res = 0;
    std::queue<int> que;
    std::vector<int> prev;
    while (true) {
        prev.assign(n, -1);
        std::queue<int>().swap(que);
        prev.at(s) = s;
        que.push(s);
        while (!que.empty() && prev.at(t) == -1) {
            int cur = que.front(); que.pop();
            for (auto p : G.at(cur)) {
                int nx = p.first;
                if (prev.at(nx) == -1 && cap.at(cur).at(nx) > 0) {
                    prev.at(nx) = cur;
                    que.push(nx);
                }
            }
        }
        if (prev.at(t) == -1) return res;
        long long inc = LINF;
        for (int i=t; prev.at(i)!=i; i=prev.at(i)) inc = std::min(inc, cap.at(prev.at(i)).at(i));
        for (int i=t; prev.at(i)!=i; i=prev.at(i)) cap.at(prev.at(i)).at(i) -= inc;
        res += inc;
    }
}
