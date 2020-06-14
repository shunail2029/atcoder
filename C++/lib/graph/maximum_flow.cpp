#include <algorithm>
#include <queue>
#include <vector>

using Graph = std::vector<std::vector<int>>;
constexpr long long LINF = 1e18;

// Edmonds-Karp algorithm
long long edmondsKarp(const Graph &G, std::vector<std::vector<long long>> &cap, const int s, const int t) {
    int n = (int)G.size();

    long long res = 0;
    std::queue<int> que;
    std::vector<int> prev;
    while (true) {
        prev.assign(n, -1);
        std::queue<int>().swap(que);
        prev[s] = s;
        que.push(s);
        while (!que.empty() && prev[t] == -1) {
            int cur = que.front(); que.pop();
            for (int nx : G[cur]) {
                if (prev[nx] == -1 && cap[cur][nx] > 0) {
                    prev[nx] = cur;
                    que.push(nx);
                }
            }
        }
        if (prev[t] == -1) return res;
        long long inc = LINF;
        for (int i=t; prev[i]!=i; i=prev[i]) inc = std::min(inc, cap[prev[i]][i]);
        for (int i=t; prev[i]!=i; i=prev[i]) cap[prev[i]][i] -= inc;
        res += inc;
    }
}
