#include <algorithm>
#include <queue>
#include <vector>

using WGraph = std::vector<std::vector<std::pair<int, long long>>>;
constexpr long long LINF = 1e18;

// Dijkstra's algorithm ダイクストラ法
long long Dijkstra(const WGraph &G, const int s, const int t) {
    int n = (int)G.size();
    std::vector<long long> dis(n, LINF);
    dis[s] = 0;
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    que.push(std::make_pair(0, s));

    while (!que.empty()) {
        auto p = que.top(); que.pop();
        int v = p.second;
        if (dis[v] < p.first) continue;
        for (auto e : G[v]) {
            if (dis[e.first] > dis[v] + e.second) {
                dis[e.first] = dis[v] + e.second;
                que.push(std::make_pair(dis[e.first], e.first));
            }
        }
    }
    return dis[t] == LINF ? -1 : dis[t];
}

// path restore 経路復元
long long Dijkstra(WGraph G, const int s, const int t, std::vector<int> &path) {
    int n = (int)G.size();
    std::vector<long long> dis(n, LINF);
    std::vector<int> prev(n, -1);
    dis[s] = 0;
    using P = std::pair<long long, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    que.push(std::make_pair(0, s));

    while (!que.empty()) {
        auto p = que.top(); que.pop();
        int v = p.second;
        if (dis[v] < p.first) continue;
        for (auto e : G[v]) {
            if (dis[e.first] > dis[v] + e.second) {
                dis[e.first] = dis[v] + e.second;
                que.push(std::make_pair(dis[e.first], e.first));
                prev[e.first] = v;
            }
        }
    }

    for (int cur = t; cur != -1; cur = prev[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    return dis[t] == LINF ? -1 : dis[t];
}

// Bellman-Ford algorithm ベルマンフォード法
long long BellmanFord(const WGraph &G, const int s, const int t) {
    int N = (int)G.size();
    std::vector<long long> dis(N, LINF);

    // seek shortest path
    dis[s] = 0;
    for (int i=0; i<N-1; ++i) {
        for (int j=0; j<N; ++j) {
            for (auto e : G[j]) {
                if (dis[e.first] > dis[j] + e.second) dis[e.first] = dis[j] + e.second;
            }
        }
    }

    // find negative loop
    for (int i=0; i<N; ++i) {
        for (auto e : G[i]) {
            if (dis[e.first] > dis[i] + e.second) return -LINF;
        }
    }

    return dis[t];
}

// restore path 経路復元
long long BellmanFord(const WGraph &G, const int s, const int t, std::vector<int> &path) {
    int N = (int)G.size();
    std::vector<long long> dis(N, LINF);
    std::vector<int> prev(N, -1);

    // seek shortest path
    dis[s] = 0;
    for (int i=0; i<N-1; ++i) {
        for (int j=0; j<N; ++j) {
            for (auto e : G[j]) {
                if (dis[e.first] > dis[j] + e.second) {
                    dis[e.first] = dis[j] + e.second;
                    prev[e.first] = i;
                }
            }
        }
    }

    // find negative loop
    for (int i=0; i<N; ++i) {
        for (auto e : G[i]) {
            if (dis[e.first] > dis[i] + e.second) return -LINF;
        }
    }

    for (int cur = t; cur != -1; cur = prev[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());

    return dis[t];
}

// Warshall–Floyd algorithm ワーシャルフロイド法
std::vector<std::vector<long long>> WarshallFloyd(const WGraph &G) {
    int n = (int)G.size();
    std::vector<std::vector<long long>> dis(n, std::vector<long long>(n, LINF));
    for (int i=0; i<n; i++) dis[i][i] = 0;
    for (int i=0; i<n; i++) {
        for (auto e : G[i]) {
            dis[i][e.first] = e.second;
        }
    }

    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    return dis;
}
