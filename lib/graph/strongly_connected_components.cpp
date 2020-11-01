#include <algorithm>
#include <vector>

using Graph = std::vector<std::vector<int>>;

// Strongly Connected Components (SCC) 強連結成分分解
class SCC {
    private:
        int N;
        Graph G, revG;
        std::vector<int> comp, ord;
        void dfs(int cur, std::vector<bool> &visited) {
            visited[cur] = true;
            for (int nx : G[cur]) {
                if (!visited[nx]) dfs(nx, visited);
            }
            ord.push_back(cur);
        }
        void rdfs(int cur, int group) {
            comp[cur] = group;
            for (int nx : revG[cur]) {
                if (comp[nx] == -1) rdfs(nx, group);
            }
        }
    public:
        SCC(const Graph &g) : N((int)g.size()), G(g), revG(N), comp(N, -1) {
            for (int i=0; i<N; ++i) {
                for (int j : G[i]) {
                    revG[j].push_back(i);
                }
            }
        }
        // build and retun number of group
        int build() {
            std::vector<bool> visited(N, false);
            for (int i=0; i<N; ++i) {
                if (!visited[i]) dfs(i, visited);
            }
            std::reverse(ord.begin(), ord.end());
            int group = 0;
            for (int idx : ord) {
                if (comp[idx] == -1) rdfs(idx, group++);
            }
            return group;
        }
        int operator[](int idx) { return comp[idx]; }
};
