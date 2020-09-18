#include <algorithm>
#include <stack>
#include <vector>

using Graph = std::vector<std::vector<int>>;

// topological sort トポロジカルソート
std::vector<int> topologicalSort(const Graph &G) {
    int n = (int)G.size();
    std::vector<int> cntIn(n);
    for (auto vec : G) {
        for (int x : vec) {
            ++cntIn[x];
        }
    }

    std::vector<int> res;
    std::stack<int> st;
    for (int i=0; i<n; i++) {
        if (cntIn[i] == 0) st.push(i);
    }
    while (!st.empty()) {
        int cur = st.top(); st.pop();
        res.push_back(cur);
        for (int x : G[cur]) {
            --cntIn[x];
            if (cntIn[x] == 0) st.push(x);
        }
    }
    return res;
}
