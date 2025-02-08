// Data structure that computes LCA and K-th ancestor using binary lifting
struct LowestCommonAncestor {
	int V = 0, lgV = 0;
	LowestCommonAncestor(int V, int root = 1) : V(V) {
		while ((1 << (lgV + 1)) <= V) {
			++lgV;
		}
		g.resize(V + 1);
	}
	void addEdge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build(int root = 1) {
		anc.assign(V + 1, vector<int>(lgV + 1));
		tin.resize(V + 1);
		tout.resize(V + 1);
		depth.resize(V + 1);
		int timer = 0;
		function<void(int, int)> dfs = [&](int u, int par) {
			tin[u] = ++timer;
			for (auto& v : g[u]) {
				if (v == par) {
					continue;
				}
				depth[v] = depth[u] + 1;
				anc[v][0] = u;
				for (int i = 1; i <= lgV; ++i) {
					anc[v][i] = anc[anc[v][i - 1]][i - 1];
				}
				dfs(v, u);
			}
			tout[u] = ++timer;
			};
		dfs(root, -1);
	}
	bool isAncestor(int u, int v) {
		return tin[u] <= tin[v] && tout[v] <= tout[u];
	}
	int lca(int u, int v) {
		if (isAncestor(u, v)) {
			return u;
		}
		if (isAncestor(v, u)) {
			return v;
		}
		for (int i = lgV; i >= 0; --i) {
			if (anc[v][i] && !isAncestor(anc[v][i], u)) {
				v = anc[v][i];
			}
		}
		return anc[v][0];
	}
	int kthAncestor(int u, int k) {
		for (int i = lgV; i >= 0; --i) {
			if ((k >> i) & 1) {
				u = anc[u][i];
			}
		}
		return u;
	}
private:
	vector<int> depth, tin, tout;
	vector<vector<int>> g;
	vector<vector<int>> anc;
};
