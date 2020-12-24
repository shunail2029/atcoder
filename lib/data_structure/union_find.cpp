#include <vector>

// Union-Find
class UnionFind {
    private :
        std::vector<int> par;
        std::vector<int> sz;
    public :
        UnionFind(int n) {
            par.resize(n);
            for (int i=0; i<n; i++) par[i] = i;
            sz.assign(n, 1);
        }
        // unite x and y
        // x and y are 0-indexed
        void unite(int x, int y) {
            const int x_par = find(x);
            const int y_par = find(y);
            if (x_par == y_par) return;

            if (sz[x_par] < sz[y_par]) {
                par[x_par] = y_par;
                sz[y_par] += sz[x_par];
            } else {
                par[y_par] = x_par;
                sz[x_par] += sz[y_par];
            }
        }
        // return root of x
        // x is 0-indexed
        int find(int x) {
            if (par[x] == x) return x;
            else return par[x] = find(par[x]);
        }
        // return whether x and y are in same group
        // x and y are 0-indexed
        bool same(int x, int y) { return find(x) == find(y); }
        int size(int x) { return sz[find(x)]; }
};

// Union-Find
class _UnionFind {
    private :
        std::vector<int> par;
    public :
        _UnionFind(int n) {
            par.resize(n);
            for (int i=0; i<n; i++) par[i] = i;
        }
        // unite x and y
        // x and y are 0-indexed
        void unite(int x, int y) {
            int xPar = find(x);
            int yPar = find(y);
            if (xPar == yPar) return;

            par[xPar] = yPar;
        }
        // return root of x
        // x is 0-indexed
        int find(int x) {
            if (par[x] == x) return x;
            else return par[x] = find(par[x]);
        }
        // return whether x and y are in same group
        // x and y are 0-indexed
        bool same(int x, int y) { return find(x) == find(y); }
};

// Union-Find with count
class _UnionFindCnt {
    private :
        std::vector<int> par;
        std::vector<int> cnt;
    public :
        _UnionFindCnt(int n) {
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
