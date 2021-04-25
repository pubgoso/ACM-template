int n, m;
vector<pair<int, int> >v[N];
int rt, son[N], sz[N], vis[N];
int dis[N][22];
void root(int now, int pre) { //找重心
	sz[now] = 1;
	son[now] = 0;
	for (auto k : v[now]) {
		if (vis[k.fi] || k.fi == pre)continue;
		root(k.fi, now);
		sz[now] += sz[k.fi];
		son[now] = max(son[now], sz[k.fi]);
	}
	son[now] = max(son[now], n - sz[now]);
	if (!rt || son[rt] > son[now]) {
		rt = now;
	}
	return ;
}
int fa[N];
void dfs(int now, int preroot) {
	if (preroot) {
		fa[now] = preroot;
	}
	vis[now] = 1;
	for (auto k : v[now]) {
		if (vis[k.fi])continue;
		rt = 0;
		n = sz[k.fi];
		root(k.fi, 0);
		root(rt, 0);
		dfs(rt, now);
	}
	return ;
}
// 点分树 建好以后 预处理一下距离
// 不然复杂度还是log^2 的
/*
 * rmq求lca
 * */
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
int T, sta[N];
LL val[N], pre[N];
int SZ[N], psz[N];

void cal(int x) {
	int _x = x;
	for (; x; x = fa[x]) {
		if (fa[x]) {
			/*
				剪掉多余的部分
			*/
		}
		/*
			加上新的
		*/
	}
	return;
}
LL get (int x) {
	for (; x; x = fa[x]) {
		/*
			注意要去掉额外的
		*/
	}
	return ans;
};
/*
	注意n在找重心的时候会变!
	root(1, 0);
	root(rt, 0);
	LCA.init(); LCA.dfs(rt, 0, 0); LCA.pre();
	dfs(rt, 0);
*/