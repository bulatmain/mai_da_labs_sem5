#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <vector>
#include <queue>

template <class T>
using vec = std::vector<T>;

template <class T>
using que = std::queue<T>;

template <class T>
using p = std::pair<T, T>;

using u32 = uint32_t;
using i32 = int32_t;

using u8 = uint8_t;
using i8 = int8_t;

template <class T>
std::ostream& operator<<(std::ostream& os, p<T> const& v) {
    os << v.first << " " << v.second;
    return os;
}

class Kuhn {
   public:
    Kuhn(vec<vec<i32>> const& graph, vec<i32> const& color)
        :   graph(graph), 
            color(color),
            n(graph.size()), 
            matching(n, -1) {}

    vec<p<i32>> findMaxMatching() {
        for (i32 u = 0; u < n; ++u) {
            if (color[u]) {
                continue;
            }
            used.assign(n, 0);
            kuhn(u);
        }

        vec<p<i32>> ans;
        for (i32 i = 0; i < n; ++i) {
            if (matching[i] != -1) {
                ans.push_back(sorted(i + 1, matching[i] + 1));
            }
        }

        return ans;
    }

   private:
    vec<vec<i32>> const& graph;
    vec<i32> const& color;
    u32 const n;
    vec<i32> matching;
    vec<i8> used;

    bool kuhn(i32 u) {
        if (used[u]) {
            return false;
        }
        used[u] = true;
        for (i32 v : graph[u]) {
            if (matching[v] == -1 || kuhn(matching[v])) {
                matching[v] = u;
                return true;
            }
        }
        return false;
    }

    template <class T>
    p<T> sorted(T const& a, T const& b) {
        if (b < a) {
            return {b, a};
        }
        return {a, b};
    }

};

vec<vec<i32>> readGraph() {
    i32 n, m;
    std::cin >> n >> m;

    vec<vec<i32>> graph(n);
    for (i32 i = 0; i < m; ++i) {
        i32 u, v;
        std::cin >> u >> v;
        --u;
        --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for (i32 i = 0; i < n; ++i) {
        std::sort(graph[i].begin(), graph[i].end());
    }

    return graph;
}

bool isBipartiteness(vec<vec<i32>> const& graph, vec<i32>& color) {
    u32 n = graph.size();
    que<i32> q;
    color.assign(n, -1);
    for (i32 i = 0; i < n; ++i) {
        if (color[i] != -1) {
            continue;
        }
        color[i] = 0;
        q.push(i);

        while (!q.empty()) {
            i32 u = q.front();
            q.pop();

            for (auto const& v : graph[u]) {
                if (color[v] == -1) {   
                    color[v] = 1 - color[u];
                    q.push(v);
                }
            }
        }
    }

    for (i32 u = 0; u < n; ++u) {
        for (auto const& v : graph[u]) {
            if (color[u] == color[v]) {
                return false;
            }
        }
    }

    return true;
}

i32 main() {
    auto graph = readGraph();

    vec<i32> color;

    if (!isBipartiteness(graph, color)) {
        std::cout << "-1\n";
        return 0;
    }

    Kuhn kuhn(graph, color);

    auto ans = kuhn.findMaxMatching();

    std::sort(ans.begin(), ans.end());

    std::cout << ans.size() << "\n";
    for (auto const& edge : ans) {
        std::cout << edge << "\n";
    }

    return 0;
}
