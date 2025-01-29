using flow_t = int;

struct Edge {
    int from, to;
    flow_t capacity, flow;
    Edge(int from, int to, flow_t capacity) : from(from), to(to), capacity(capacity), flow(0) {

    }
};

// Dinic's algorithm for max flow on directed graphs
struct MaxFlow {
    int V, E = 0;
    MaxFlow(int V) : V(V), E(0) {
        g.resize(V);
    }
    void addEdge(int from, int to, flow_t capacity) {
        g[from].push_back(E++);
        edges.emplace_back(from, to, capacity);
        g[to].push_back(E++);
        edges.emplace_back(to, from, 0);
    }
    flow_t flow(int source, int sink) {
        vector<int> level(V), ptr(V);
        function<bool()> bfs = [&]() {
            fill(level.begin(), level.end(), -1);
            queue<int> q;
            level[source] = 0;
            q.push(source);
            while (q.size()) {
                int u = q.front();
                for (auto& i : g[u]) {
                    if (edges[i].flow == edges[i].capacity) { // saturated edge
                        continue;
                    }
                    if (level[edges[i].to] != -1) { // already marked
                        continue;
                    }
                    level[edges[i].to] = level[u] + 1;
                    q.push(edges[i].to);
                }
                q.pop();
            }
            return level[sink] != -1; // found a augmenting path
        };
        function<flow_t(int, flow_t)> dfs = [&](int u, flow_t pushed) {
            if (pushed == (flow_t)0) {
                return (flow_t)0;
            }
            if (u == sink) {
                return pushed;
            }
            for (auto& which = ptr[u]; which < g[u].size(); ++which) {
                int i = g[u][ptr[u]];
                if (level[edges[i].to] != level[u] + 1) { // not an important edge
                    continue;
                }
                flow_t returned = dfs(edges[i].to, min(pushed, edges[i].capacity - edges[i].flow));
                if (returned == 0) { // we can't push anymore flow through this node
                    continue;
                }
                edges[i].flow += returned;
                edges[i ^ 1].flow -= returned;
                return returned;
            }
            return (flow_t)0;
        };
        flow_t f = 0;
        while (bfs()) {
            fill(ptr.begin(), ptr.end(), 0);
            while (flow_t pushed = dfs(source, numeric_limits<flow_t>::max())) {
                f += pushed;
            }
        }
        return f;
    }
    vector<vector<int>> g;
    vector<Edge> edges;
};
