#include <utility>
#include <vector>

using Graph = std::vector<std::vector<int>>;

// Lowest Common Ancestor 最小共通祖先
class LCA {
    private:
        int K, N;
        Graph G;
        std::vector<int> dis;
        std::vector<std::vector<int>> par;
    public:
        LCA(const Graph &g) : N((int)g.size()), G(g) {
            K = 1;
            while ((1 << K) < N) ++K;
            dis.assign(N, -1);
            par.assign(K, std::vector<int>(N, -1));
        }
        void build(int root = 0) {
            dfs(root, -1, 0);
            for (int i=1; i<K; ++i) {
                for (int j=0; j<N; ++j) {
                    if (par[i-1][j] == -1) par[i][j];
                    else par[i][j] = par[i-1][par[i-1][j]];
                }
            }
        }
        void dfs(int cur, int pre, int depth) {
            dis[cur] = depth;
            par[0][cur] = pre;
            for (int nx : G[cur]) {
                if (nx != pre) dfs(nx, cur, depth+1);
            }
        }
        int query(int u, int v) {
            if (dis[u] < dis[v]) std::swap(u, v);
            int dif = dis[u] - dis[v];
            for (int i=0; i<K; ++i) {
                if (dif & (1<<i)) u = par[i][u];
            }
            if (u == v) return u;
            for (int i=K-1; i>=0; --i) {
                if (par[i][u] != par[i][v]) {
                    u = par[i][u];
                    v = par[i][v];
                }
            }
            return par[0][u];
        }
};
