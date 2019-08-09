#include <vector>

class union_find {
    private :
        std::vector<int> par;
    public :
        union_find(int);
        int find(int);
        bool same(int, int);
        void unite(int, int);
};

union_find::union_find(int n) {
    par.resize(n);
    for (int i=0; i<n; i++) {
        par.at(i) = i;
    }
}

int union_find::find(int x) {
    if (par.at(x) == x) return x;
    else return par.at(x) = find(par.at(x));
}

bool union_find::same(int x, int y) {
    return find(x) == find(y);
}

void union_find::unite(int x, int y) {
    int x_par = find(x);
    int y_par = find(y);
    if (x_par == y_par) return;

    par.at(x_par) = y_par;
}
