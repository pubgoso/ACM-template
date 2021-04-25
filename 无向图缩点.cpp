int From[N], Laxt[N], To[N << 2], Next[N << 2], cnt;
int low[N], dfn[N], times, q[N], head, scc_cnt, scc[N];
vector<int>G[N];
int dis[N], S, T, ans;
void add(int u, int v)
{
	Next[++cnt] = Laxt[u]; From[cnt] = u;
	Laxt[u] = cnt; To[cnt] = v;
}
void tarjan(int u, int fa)
{
	dfn[u] = low[u] = ++times;
	q[++head] = u;
	for (int i = Laxt[u]; i; i = Next[i]) {
		if (To[i] == fa) continue;
		if (!dfn[To[i]]) {
			tarjan(To[i], u);
			low[u] = min(low[u], low[To[i]]);
		}
		else low[u] = min(low[u], dfn[To[i]]);
	}
	if (low[u] == dfn[u]) {
		scc_cnt++;
		while (true) {
			int x = q[head--];
			scc[x] = scc_cnt;
			if (x == u) break;
		}
	}
}
void init()
{
	memset(Laxt, 0, sizeof(Laxt));
	cnt = 0;
}
int main()
{
	init();
	int N, M, u, v, i, j;
	scanf("%d%d", &N, &M);
	for (i = 1; i <= M; i++) {
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
	}
	tarjan(1, 0);
	for (i = 1; i <= N; i++) {
		for (j = Laxt[i]; j; j = Next[j]) {
			if (scc[i] != scc[To[j]])
				G[scc[i]].push_back(scc[To[j]]);
		}
	}

	return 0;
}