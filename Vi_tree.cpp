struct Virtual_tree {
	vector<int>v[N], g[N];
	int dep[N], f[N][22], st[N], top;
	int n, r, dfn[N], CNT;
	void init(int _n, int _r) {
		n = _n; r = _r; CNT = 0;
		for (int i = 1; i <= n; i++) {
			v[i].clear();
			g[i].clear();
		}
	}
	int lca(int u, int v) {
		if (dep[u] < dep[v])swap(u, v);
		for (int i = 19; i >= 0; i--)if ((dep[u] - dep[v]) >> i & 1)u = f[u][i];
		if (u == v)return u;
		for (int i = 19; i >= 0; i--)if (f[u][i] != f[v][i])u = f[u][i], v = f[v][i];
		return f[u][0];
	}
	void dfs(int x, int y) {
		f[x][0] = y; dfn[x] = ++CNT;
		dep[x] = dep[y] + 1;
		for (int j = 1; j <= 19; j++) {
			f[x][j] = f[f[x][j - 1]][j - 1];
		}
		for (auto k : v[x])if (k != y) {
				dfs(k, x);
			}
	}
	void ins(int u) {
		if (top == 1) {st[++top] = u; return ;}
		int lc = lca(u, st[top]);
		if (lc == st[top]) {st[++top] = u; return;}
		while (top > 1 && dfn[lc] <= dfn[st[top - 1]]) {
			g[st[top - 1]].pb(st[top]);
			top--;
		}
		if (lc != st[top]) {
			g[lc].pb(st[top]);
			st[top] = lc;
		}
		st[++top] = u;
	}
	/*
	  void ins(int u) {
	    if(top==1){st[++top]=u;return;}
	    int lc=lca(u,st[top]);
	    if(dep[lc]==dep[st[top]]){st[++top]=u;return;}
	    while(top>1 && dep[lc]<=dep[st[top-1]]){
	      g[st[top-1]].pb(st[top]);
	      top--;
	    }
	    if(dep[lc]!=dep[st[top]]){
	      g[lc].pb(st[top]);
	      st[top]=lc;
	    }
	    st[++top]=u;
	  }
	*/
	void in(vector<int>&da) {
		sort(da.begin(), da.end(), [&](int x, int y) {return dfn[x] < dfn[y];});
		top = 0; st[++top] = r;
		for (auto k : da) {
			if (k != 1)ins(k);
		}
		while (top > 1) {
			g[st[top - 1]].pb(st[top]);
			top--;
		}
	}
	int dis(int x, int y) {
		return dep[x] + dep[y] - 2 * dep[lca(x, y)];
	}
} G;