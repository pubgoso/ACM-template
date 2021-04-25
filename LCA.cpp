struct lca_rmq {
	int l[N << 1], id = 0;
	int lg[N << 1], vis[N << 1], deep[N << 1];
	int f[N << 1][22];
	int de[N];
	void init() {
		id = 0;
		for (int i = 1; i < N << 1; i++)lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
	}
	void dfs(int x, int y, int dep) {
		l[x] = ++id;
		vis[id] = x;
		deep[id] = dep;
		de[x] = dep;
		for (auto k : v[x]) {
			if (k.fi != y) {
				dfs(k.fi, x, dep + 1);
				vis[++id] = x;
				deep[id] = dep;
			}
		}
	}
	void pre() {
		for (int i = 1; i <= id; i++)f[i][0] = i;
		for (int i = 1; (1 << i) <= id; i++) {
			for (int j = 1; j + (1 << i) - 1 <= id; j++) {
				int a = f[j][i - 1];
				int b = f[j + (1 << (i - 1))][i - 1];
				if (deep[a] <= deep[b])f[j][i] = a;
				else f[j][i] = b;
			}
		}
	}
	int query(int x, int y) {
		int dx = l[x], dy = l[y];
		if (dx > dy)swap(dx, dy);
		int k = lg[dy - dx + 1] - 1;
		int a = f[dx][k], b = f[dy - (1 << k) + 1][k];
		if (deep[a] <= deep[b])return vis[a];
		else return vis[b];
	}
	int dis(int x, int y) {
		return de[x] + de[y] - 2 * de[query(x, y)];
	}
} LCA;