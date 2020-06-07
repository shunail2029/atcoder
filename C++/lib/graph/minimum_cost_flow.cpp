#include <algorithm>
#include <queue>
#include <vector>

using WGraph = std::vector<std::vector<std::pair<int, long long>>>;
constexpr long long LINF = 1e18;

long long primalDual(const WGraph &G, std::vector<std::vector<long long>> &cap, int s, int t, long long flow) {
    int n = (int)G.size();
    WGraph g(n);
    for (int i=0; i<n; ++i) {
        for (auto p : G.at(i)) {
            g.at(i).push_back(p);
            g.at(p.first).push_back({i, -p.second});
        }
    }

    long long res = 0;
    std::vector<long long> h(n), dis(n, LINF);
    std::vector<int> prev(n);
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    while (flow > 0) {
        dis.assign(n, LINF);
        dis.at(s) = 0;
        que.push({0, s});
        while (!que.empty()) {
            auto p = que.top(); que.pop();
            int cur = p.second;
            if (dis.at(cur) < p.first) continue;
            for (auto q : g.at(cur)) {
                int nx = q.first;
                if (cap.at(cur).at(nx) > 0 && dis.at(nx) > dis.at(cur) + q.second + h.at(cur) - h.at(nx)) {
                    dis.at(nx) = dis.at(cur) + q.second + h.at(cur) - h.at(nx);
                    prev.at(nx) = cur;
                    que.push({dis.at(nx), nx});
                }
            }
        }
        if (dis.at(t) == LINF) return -1;
        for (int i=0; i<n; ++i) h.at(i) += dis.at(i);

        long long d = flow;
        for (int i=t; i!=s; i=prev.at(i)) d = std::min(d, cap.at(prev.at(i)).at(i));
        flow -= d;
        res += d * h.at(t);
        for (int i=t; i!=s; i=prev.at(i)) {
            cap.at(prev.at(i)).at(i) -= d;
            cap.at(i).at(prev.at(i)) += d;
        }
    }
    return res;
}
