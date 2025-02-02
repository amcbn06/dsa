struct MaxMatching {
    int V;
    vector<int> color;
    vector<vector<int>> g;
    vector<int> match;
    MaxMatching(int V) : V(V) {
        color.resize(V);
        match.assign(V, -1);
        g.resize(V);
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int matching() {
        vector<bool> vis(V);
        function<void(int)> colorGraph = [&](int u) {
            vis[u] = true;
            for (auto& v : g[u]) {
                if (!vis[v]) {
                    color[v] = color[u] ^ 1;
                    colorGraph(v);
                }
            }
        };
        function<bool(int)> findPath = [&](int u) {
            vis[u] = true;
            for (auto& v : g[u]) {
                if (match[v] == -1 || (!vis[match[v]] && findPath(match[v]))) {
                    match[u] = v;
                    match[v] = u;
                    return true;
                }
            }
            return false;
            };
        for (int i = 0; i < V; ++i) {
            if (!vis[i]) {
                colorGraph(i);
            }
        }
        int m = 0, ok = true;
        while (ok) {
            ok = false;
            fill(vis.begin(), vis.end(), false);
            for (int u = 0; u < V; ++u) {
                if (color[u] && match[u] == -1 && !vis[u] && findPath(u)) {
                    ok = true;
                    ++m;
                }
            }
        }
        return m;
    }
};
