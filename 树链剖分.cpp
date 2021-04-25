int siz[N], fa[N], de[N], to[N], a[N], son[N];
void dfs1(int now, int pre, int d) {
	siz[now] = 1;
	fa[now] = pre;
	de[now] = d;
	int cnt = -1;
	for (auto k : v[now]) {
		if (k == pre)continue;
		dfs1(k, now, d + 1);
		siz[now] += siz[k];
		if (siz[k] > cnt) {
			cnt = siz[k];
			son[now] = k;
		}
	}
}
void dfs2(int now, int pre) {
	to[now] = pre;
	a[now] = ++cnt;
	if (!son[now])return ;
	dfs2(son[now], pre);
	for (auto k : v[now]) {
		if (k == fa[now] || k == son[now])continue;
		dfs2(k, k);
	}
}
int find_lca(int l, int r) {
	int res = 0;
	while (to[l] != to[r]) {
		if (de[to[l]] < de[to[r]])swap(l, r);
		l = fa[to[l]];
	}
	if (de[l] > de[r])swap(l, r);
	return l;
}