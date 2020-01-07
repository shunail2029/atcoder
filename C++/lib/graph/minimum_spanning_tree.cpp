#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

using WGraph = std::vector<std::vector<std::pair<int, long long>>>;

// Prim's algorithm
long long prim(const WGraph &G) {
    int n = (int)G.size();
    std::vector<bool> used(n, false);
    long long res = 0;
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    used.at(0) = true;
    for (auto e : G.at(0)) {
        que.push(std::make_pair(e.second, e.first));
    }
    while (!que.empty()) {
        auto p = que.top();
        que.pop();
        int v = p.second;
        if (used.at(v)) {
            continue;
        }
        used.at(v) = true;
        res += p.first;
        for (auto e : G.at(v)) {
            if (!used.at(e.first)) {
                que.push(std::make_pair(e.second, e.first));
            }
        }
    }
    return res;
}

// Kruskal's algorithm クラスカル法
// use union_find
#include "../data_structure/union_find.cpp"
long long kruskal(const WGraph &G) {
    int n = (int)G.size();
    std::vector<std::tuple<long long, int, int>> edge;
    for (int i=0; i<n; i++) {
        for (auto e : G.at(i)) {
            edge.push_back(std::make_tuple(e.second, i, e.first));
        }
    }

    sort(edge.begin(), edge.end());
    UnionFind uf(n);
    long long res = 0;
    for (auto e : edge) {
        if (!uf.same(std::get<1>(e), std::get<2>(e))) {
            uf.unite(std::get<1>(e), std::get<2>(e));
            res += std::get<0>(e);
        }
    }
    return res;
}
