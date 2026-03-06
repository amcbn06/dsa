// Data structure that computes LCA in O(1) per query using RMQ
struct LowestCommonAncestor {
	int V = 0;
	LowestCommonAncestor(int V, int root = 1) : V(V) {
		g.resize(V + 1);
	}
	void addEdge(int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void build() {
		pos.resize(V + 1);
		depth.resize(V + 1);
		function<void(int, int)> dfs = [&](int u, int par) {
			pos[u] = tour.size();
			tour.push_back(u);
			for (auto& v : g[u]) {
				if (v == par) {
					continue;
				}
				depth[v] = depth[u] + 1;
				dfs(v, u);
				tour.push_back(u);
			}
		};
		dfs(1, -1);
		int len = tour.size();
		lg2.resize(len + 1);
		for (int i = 2; i <= len; ++i) {
			lg2[i] = lg2[i >> 1] + 1;
		}
		rmq.resize(lg2[len] + 1);
		rmq[0].assign(tour.begin(), tour.end());
		for (int p = 1; (1 << p) <= len; ++p) {
			rmq[p].resize(len - (1 << p) + 1);
			for (int i = 0; i < len - (1 << p) + 1; ++i) {
				rmq[p][i] = compare(rmq[p - 1][i], rmq[p - 1][i + (1 << (p - 1))]);
			}
		}
	}
	int lca(int u, int v) {
		int l = pos[u], r = pos[v];
		if (l > r) {
			swap(l, r);
		}
		int p = lg2[r - l + 1];
		return compare(rmq[p][l], rmq[p][r - (1 << p) + 1]);
	}
private:
	vector<int> depth, pos;
	vector<vector<int>> g;
	vector<int> tour, lg2;
	vector<vector<int>> rmq;
	int compare(int u, int v) {
		return depth[u] < depth[v] ? u : v;
	}
};
