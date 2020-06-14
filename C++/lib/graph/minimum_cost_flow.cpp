#include <algorithm>
#include <queue>
#include <vector>

using WGraph = std::vector<std::vector<std::pair<int, long long>>>;
constexpr long long LINF = 1e18;

long long primalDual(const WGraph &G, std::vector<std::vector<long long>> &cap, int s, int t, long long flow) {
    int n = (int)G.size();
    WGraph g(n);
    for (int i=0; i<n; ++i) {
        for (auto p : G[i]) {
            g[i].push_back(p);
            g[p.first].push_back({i, -p.second});
        }
    }

    long long res = 0;
    std::vector<long long> h(n), dis(n, LINF);
    std::vector<int> prev(n);
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    while (flow > 0) {
        dis.assign(n, LINF);
        dis[s] = 0;
        que.push({0, s});
        while (!que.empty()) {
            auto p = que.top(); que.pop();
            int cur = p.second;
            if (dis[cur] < p.first) continue;
            for (auto q : g[cur]) {
                int nx = q.first;
                if (cap[cur][nx] > 0 && dis[nx] > dis[cur] + q.second + h[cur] - h[nx]) {
                    dis[nx] = dis[cur] + q.second + h[cur] - h[nx];
                    prev[nx] = cur;
                    que.push({dis[nx], nx});
                }
            }
        }
        if (dis[t] == LINF) return -1;
        for (int i=0; i<n; ++i) h[i] += dis[i];

        long long d = flow;
        for (int i=t; i!=s; i=prev[i]) d = std::min(d, cap[prev[i]][i]);
        flow -= d;
        res += d * h[t];
        for (int i=t; i!=s; i=prev[i]) {
            cap[prev[i]][i] -= d;
            cap[i][prev[i]] += d;
        }
    }
    return res;
}
