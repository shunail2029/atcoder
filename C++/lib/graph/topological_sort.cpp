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
            cntIn.at(x)++;
        }
    }

    std::vector<int> res;
    std::stack<int> st;
    for (int i=0; i<n; i++) {
        if (cntIn.at(i) == 0) {
            st.push(i);
        }
    }
    while (!st.empty()) {
        int cur = st.top(); st.pop();
        res.push_back(cur);
        for (int x : G.at(cur)) {
            cntIn.at(x)--;
            if (cntIn.at(x) == 0) {
                st.push(x);
            }
        }
    }

    return res;
}
