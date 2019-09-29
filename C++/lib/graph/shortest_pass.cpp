#include <algorithm>
#include <queue>
#include <vector>

using WGraph = std::vector<std::vector<std::pair<int, long long>>>;

// Dijkstra's algorithm ダイクストラ法
long long dijkstra(WGraph G, int s, int t) {
    int n = (int)G.size();
    std::vector<long long> dis(n, 1e16);
    dis.at(s) = 0;
    std::priority_queue<std::pair<long long, int>> que;
    que.push(std::make_pair(0, s));

    while (!que.empty()) {
        auto p = que.top();
        que.pop();
        int v = p.second;
        if (dis.at(v) < p.first) {
            continue;
        }
        for (auto e : G.at(v)) {
            if (dis.at(e.first) > dis.at(v) + e.second) {
                dis.at(e.first) = dis.at(v) + e.second;
                que.push(std::make_pair(dis.at(e.first), e.first));
            }
        }
    }
    return dis.at(t) == 1e16 ? -1 : dis.at(t);
}

// path restore 経路復元
long long dijkstra(WGraph G, int s, int t, std::vector<int> &path) {
    int n = (int)G.size();
    std::vector<long long> dis(n, 1e16);
    std::vector<int> prev(n, -1);
    dis.at(s) = 0;
    std::priority_queue<std::pair<long long, int>> que;
    que.push(std::make_pair(0, s));

    while (!que.empty()) {
        auto p = que.top();
        que.pop();
        int v = p.second;
        if (dis.at(v) < p.first) {
            continue;
        }
        for (auto e : G.at(v)) {
            if (dis.at(e.first) > dis.at(v) + e.second) {
                dis.at(e.first) = dis.at(v) + e.second;
                que.push(std::make_pair(dis.at(e.first), e.first));
                prev.at(e.first) = v;
            }
        }
    }

    for (int cur = t; cur != -1; cur = prev.at(cur)) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    return dis.at(t) == 1e16 ? -1 : dis.at(t);
}

// Bellman-Ford algorithm ベルマンフォード法
long long bellman_ford(WGraph G, int s, int t) {
    int n = G.size();
    std::vector<long long> dis(n);
    
    // find negative loop
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (auto e : G.at(j)) {
                if (dis.at(e.first) > dis.at(j) + e.second) {
                    dis.at(e.first) = dis.at(j) + e.second;
                    if (i == n-1) {
                        return (long long)-1e16;
                    }
                }
            }
        }
    }

    // seek shortest path
    for (int i=0; i<n; i++) {
        dis.at(i) = 1e16;
    }
    dis.at(s) = 0;
    while (true) {
        bool update = false;
        for (int i=0; i<n; i++) {
            for (auto e : G.at(i)) {
                if (dis.at(e.first) > dis.at(i) + e.second) {
                    dis.at(e.first) = dis.at(i) + e.second;
                    update = true;
                }
            }
        }
        if (!update) {
            break;
        }
    }
    return dis.at(t);
}

// restore path 経路復元
long long bellman_ford(WGraph G, int s, int t, std::vector<int> &path) {
    int n = G.size();
    std::vector<long long> dis(n);
    
    // find negative loop
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (auto e : G.at(j)) {
                if (dis.at(e.first) > dis.at(j) + e.second) {
                    dis.at(e.first) = dis.at(j) + e.second;
                    if (i == n-1) {
                        return (long long)-1e16;
                    }
                }
            }
        }
    }

    // seek shortest path
    std::vector<int> prev(n, -1);
    for (int i=0; i<n; i++) {
        dis.at(i) = 1e16;
    }
    dis.at(s) = 0;
    while (true) {
        bool update = false;
        for (int i=0; i<n; i++) {
            for (auto e : G.at(i)) {
                if (dis.at(e.first) > dis.at(i) + e.second) {
                    dis.at(e.first) = dis.at(i) + e.second;
                    update = true;
                    prev.at(e.first) = i;
                }
            }
        }
        if (!update) {
            break;
        }
    }

    for (int cur = t; cur != -1; cur = prev.at(cur)) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    return dis.at(t);
}

// Warshall–Floyd algorithm ワーシャルフロイド法
std::vector<std::vector<long long>> warshall_floyd(WGraph G) {
    int n = G.size();
    std::vector<std::vector<long long>> dis(n, std::vector<long long>(n, 1e16));
    for (int i=0; i<n; i++) {
        dis.at(i).at(i) = 0;
    }
    for (int i=0; i<n; i++) {
        for (auto e : G.at(i)) {
            dis.at(i).at(e.first) = e.second;
        }
    }

    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                dis.at(i).at(j) = std::min(dis.at(i).at(j), dis.at(i).at(k) + dis.at(k).at(j));
            }
        }
    }

    return dis;
}