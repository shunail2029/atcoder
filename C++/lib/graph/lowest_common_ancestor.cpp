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
                    if (par.at(i-1).at(j) == -1) par.at(i).at(j);
                    else par.at(i).at(j) = par.at(i-1).at(par.at(i-1).at(j));
                }
            }
        }
        void dfs(int cur, int pre, int depth) {
            dis.at(cur) = depth;
            par.at(0).at(cur) = pre;
            for (int nx : G.at(cur)) {
                if (nx != pre) dfs(nx, cur, depth+1);
            }
        }
        int query(int u, int v) {
            if (dis.at(u) < dis.at(v)) std::swap(u, v);
            int dif = dis.at(u) - dis.at(v);
            for (int i=0; i<K; ++i) {
                if (dif & (1<<i)) u = par.at(i).at(u);
            }
            if (u == v) return u;
            for (int i=K-1; i>=0; --i) {
                if (par.at(i).at(u) != par.at(i).at(v)) {
                    u = par.at(i).at(u);
                    v = par.at(i).at(v);
                }
            }
            return par.at(0).at(u);
        }
};
