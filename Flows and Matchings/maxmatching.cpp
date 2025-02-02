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
        assert(0 <= u && u < V);
        assert(0 <= v && v < V);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int matching() {
        vector<bool> vis(V);
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
    vector<int> minimumVertexCover() {
        vector<int> mvc(V);
        function<void(int)> dfs = [&](int u) {
            mvc[u] = true;
            for (auto& v : g[u]) {
                if (!mvc[v]) {
                    mvc[v] = true;
                    if (match[v] != -1) {
                        dfs(match[v]);
                    }
                }
            }
            };
        for (int i = 0; i < V; ++i) {
            if (color[i] && match[i] == -1 && !mvc[i]) {
                dfs(i);
            }
        }
        vector<int> nodes;
        for (int i = 0; i < V; ++i) {
            if (color[i]) {
                if (!mvc[i]) {
                    nodes.push_back(i);
                }
            }
            else if (mvc[i]) {
                nodes.push_back(i);
            }
        }
        return nodes;
    }
};
