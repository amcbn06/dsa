// Works with nodes in range [0, __size)
struct UnionFind {
	vector<int> parent, size;
	UnionFind(int __size) {
		parent.resize(__size);
		size.resize(__size);
		for (int i = 0; i < __size; ++i) {
			parent[i] = i;
			size[i] = 1;
		}
	}
	int find(int x) {
		return parent[x] == x ? x : (parent[x] = find(parent[x]));
	}
	void merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return;
		}
		if (size[x] < size[y]) {
			swap(x, y);
		}
		parent[y] = x;
		size[x] += size[y];
	}
	bool connected(int x, int y) {
		return find(x) == find(y);
	}
};
