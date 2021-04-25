#include<bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define LL long long
using namespace std;
const int N = 1e4 + 11;
int n, m;
vector<pii>v[N];
int q[N];
int rt, son[N], sz[N], vis[N];
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
int a[N], dis[10000003];
int md[N], MK, cnt;
void getdis(int now, int pre, int di) {
	/*处理细节*/
}
int qa[N], tmp;
void get(int now, int pre) {
	/*一些处理细节*/
	for (auto k : v[now]) {
		if (k.fi == pre || vis[k.fi])continue;
		cnt = 0;
		getdis(k.fi, now, k.se);
		/*统计一下答案*/
	}
}
void dfs(int now) {
	vis[now] = 1;
	get(now, 0);
	for (auto k : v[now]) {
		if (vis[k.fi])continue;
		rt = 0;
		n = sz[k.fi];
		root(k.fi, 0);
		root(rt, 0);
		dfs(rt);
	}
	return ;
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i < n; i++) {
		int s, t, w;
		scanf("%d%d%d", &s, &t, &w);
		v[s].pb({t, w});
		v[t].pb({s, w});
	}
	root(1, 0);
	root(rt, 0);
	dfs(rt);

	return 0;
}