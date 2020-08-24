#include <algorithm>
#include <queue>
#include <vector>

using Graph = std::vector<std::vector<int>>;
constexpr long long LINF = 1e18;

// Edmonds-Karp algorithm
long long EdmondsKarp(const Graph &G, std::vector<std::vector<long long>> &cap, const int s, const int t) {
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
        for (int i=t; prev[i]!=i; i=prev[i]) cap[prev[i]][i] -= inc, cap[i][prev[i]] += inc;
        res += inc;
    }
}

// Dinic's algorithm
class Dinic {
    private:
        int N;
        Graph G;
        std::vector<int> level, iter;
        std::vector<std::vector<long long>> cap;
        std::queue<int> que;
        void bfs(int s) {
            std::fill(level.begin(), level.end(), -1);
            level[s] = 0;
            que.push(s);
            while (!que.empty()) {
                int cur = que.front(); que.pop();
                for (int nx : G[cur]) {
                    if (cap[cur][nx] > 0 && level[nx] < 0) {
                        level[nx] = level[cur] + 1;
                        que.push(nx);
                    }
                }
            }
        }
        long long dfs(int s, int t, long long f) {
            if (s == t) return f;
            for (int &i=iter[s]; i<(int)G[s].size(); ++i) {
                int nx = G[s][i];
                if (cap[s][nx] > 0 && level[s] < level[nx]) {
                    long long d = dfs(nx, t, std::min(f, cap[s][nx]));
                    if (d > 0) {
                        cap[s][nx] -= d;
                        cap[nx][s] += d;
                        return d;
                    }
                }
            }
            return 0;
        }
    public:
        Dinic(const Graph &G, const std::vector<std::vector<long long>> &cap) : N((int)G.size()), G(G), level(N), iter(N), cap(cap) {}
        long long solve(int s, int t) {
            long long flow = 0;
            while (true) {
                bfs(s);
                if (level[t] < 0) return flow;
                std::fill(iter.begin(), iter.end(), 0);
                long long f;
                while ((f = dfs(s, t, LINF)) > 0) flow += f;
            }
        }
};
