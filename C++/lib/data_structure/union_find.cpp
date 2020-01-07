#include <vector>

class UnionFind {
    protected :
        std::vector<int> par;
    public :
        UnionFind(int n) {
            par.resize(n);
            for (int i=0; i<n; i++) par.at(i) = i;
        }
        int find(int x) {
            if (par.at(x) == x) return x;
            else return par.at(x) = find(par.at(x));
        }
        bool same(int x, int y) { return find(x) == find(y); }
        virtual void unite(int x, int y) {
            int xPar = find(x);
            int yPar = find(y);
            if (xPar == yPar) return;

            par.at(xPar) = yPar;
        }
};

// Union-Find with count
class UnionFindCnt : public UnionFind {
    private :
        std::vector<int> cnt;
    public :
        UnionFindCnt(int n) : UnionFind(n) {
            cnt.resize(n);
            for (int i=0; i<n; i++) cnt.at(i) = 1;
        }
        int size(int x) { return cnt.at(find(x)); }
        void unite(int x, int y) {
            const int x_par = find(x);
            const int y_par = find(y);
            if (x_par == y_par) return;

            par.at(x_par) = y_par;
            cnt.at(y_par) += cnt.at(x_par);
            cnt.at(x_par) = 0;
        }
};
