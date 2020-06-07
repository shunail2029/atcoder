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
        prev.at(s) = s;
        que.push(s);
        while (!que.empty() && prev.at(t) == -1) {
            int cur = que.front(); que.pop();
            for (int nx : G.at(cur)) {
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
