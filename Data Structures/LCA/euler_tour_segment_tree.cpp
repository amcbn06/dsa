// Data structure that precomputes LCA in O(n) using Segment Tree
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
		len = tour.size();
		t.resize(4 * len + 1);
		build(1, 0, len - 1);
	}
	int lca(int u, int v) {
		int l = pos[u], r = pos[v];
		if (l > r) {
			swap(l, r);
		}
		return query(1, 0, len - 1, l, r);
	}
private:
	vector<int> depth, pos;
	vector<vector<int>> g;
	int len;
	vector<int> tour, t;
	int compare(int u, int v) {
		return depth[u] < depth[v] ? u : v;
	}
	void build(int node, int l, int r) {
		if (l == r) {
			t[node] = tour[l];
			return;
		}
		int mid = (l + r) / 2;
		build(node << 1, l, mid);
		build(node << 1 | 1, mid + 1, r);
		t[node] = compare(t[node << 1], t[node << 1 | 1]);
	}
	int query(int node, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return t[node];
		}
		int mid = (l + r) / 2;
		if (ql <= mid) {
			if (mid < qr) {
				return compare(query(node << 1, l, mid, ql, qr), query(node << 1 | 1, mid + 1, r, ql, qr));
			}
			else {
				return query(node << 1, l, mid, ql, qr);
			}
		}
		else {
			return query(node << 1 | 1, mid + 1, r, ql, qr);
		}
	}
};
