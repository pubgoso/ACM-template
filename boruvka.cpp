struct Boruvka {
	//每次从所有联通快找到连出去的最小权值的边 ，权值相同，编号小的为小
	int f[N], use[N], best[N];
	void init() {
		for (int i = 1; i <= n; i++)f[i] = i, best[i] = 0;
		for (int i = 1; i <= m; i++)use[i] = 0;
	}
	int find(int x) {
		return f[x] == x ? x : (f[x] = find(f[x]));
	}
	int better(int x, int y) {
		if (!y)return 1;
		if (w[x] < w[y])return 1;
		return x < y;
	}
	LL get() {
		int merge = 0;
		LL sum = 0;
		while (merge != n - 1) {
			for (int i = 1; i <= m; i++) {
				if (use[i])continue;
				int x = find(s[i]), y = find(t[i]);
				if (x == y)continue;
				if (better(i, best[x]))best[x] = i;
				if (better(i, best[y]))best[y] = i;
			}
			for (int i = 1; i <= n; i++) {
				if (best[i]) {
					int x = find(s[best[i]]), y = find(t[best[i]]);
					if (x != y) {
						use[best[i]] = 1;
						f[x] = y;
						merge++;
						sum += w[best[i]];
					}
					best[i] = 0;
				}
			}
		}
		return sum;
	}
} g;