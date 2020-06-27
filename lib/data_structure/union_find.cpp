#include <vector>

// Union-Find
class UnionFind {
    private :
        std::vector<int> par;
    public :
        UnionFind(int n) {
            par.resize(n);
            for (int i=0; i<n; i++) par[i] = i;
        }
        void unite(int x, int y) {
            int xPar = find(x);
            int yPar = find(y);
            if (xPar == yPar) return;

            par[xPar] = yPar;
        }
        int find(int x) {
            if (par[x] == x) return x;
            else return par[x] = find(par[x]);
        }
        bool same(int x, int y) { return find(x) == find(y); }
};

// Union-Find with count
class UnionFindCnt {
    private :
        std::vector<int> par;
        std::vector<int> cnt;
    public :
        UnionFindCnt(int n) {
            par.resize(n);
            for (int i=0; i<n; i++) par[i] = i;
            cnt.assign(n, 1);
        }
        void unite(int x, int y) {
            const int x_par = find(x);
            const int y_par = find(y);
            if (x_par == y_par) return;

            par[x_par] = y_par;
            cnt[y_par] += cnt[x_par];
            cnt[x_par] = 0;
        }
        int find(int x) {
            if (par[x] == x) return x;
            else return par[x] = find(par[x]);
        }
        bool same(int x, int y) { return find(x) == find(y); }
        int size(int x) { return cnt[find(x)]; }
};
