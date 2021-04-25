#include <bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5, M = 5e4 + 5;
const int inf = 1e9;

# define pi pair<int, int>

int n, m, s, t;

namespace Primal {
int Ecnt = 1, first[N], nex[M * 2], arr[M * 2], cap[M * 2], cost[M * 2];
int dis[N], h[N], pree[N], prev[N], F, C;

template <typename T>
inline void Min(T &a, T b) {
	if (a > b) a = b;
}
inline void Ad(int u, int v, int c, int w) {
	nex[++Ecnt] = first[u], first[u] = Ecnt, arr[Ecnt] = v, cap[Ecnt] = c, cost[Ecnt] = w;
}
inline void add(int u, int v, int c, int w) {
	Ad(u, v, c, w), Ad(v, u, 0, -w);
}
void Dijkstra() {
	static priority_queue<pi, vector<pi>, greater<pi> > q;
	for (; !q.empty(); q.pop());
	fill(dis, dis + 1 + n, -1);
	dis[s] = 0, q.push(pi(0, s));
	while (!q.empty()) {
		pi now = q.top(); q.pop();
		int u = now.second;
		if (dis[u] < now.first) continue;
		for (int i = first[u]; i; i = nex[i]) {
			static int v; v = arr[i];
			if (!cap[i]) continue;
			if (dis[v] < 0 || dis[v] > dis[u] + cost[i] + h[u] - h[v]) {
				dis[v] = dis[u] + cost[i] + h[u] - h[v];
				prev[v] = u, pree[v] = i;
				q.push(pi(dis[v], v));
			}
		}
	}
}
pi solve(int s, int t) {
	fill(h, h + 1 + n, 0);
	for (int f = inf; f > 0; ) {
		Dijkstra();
		// cout<<f<<endl;
		if (dis[t] < 0) break;
		for (int i = 1; i <= n; ++i) // be careful this for
			h[i] += (dis[i] != -1) ? dis[i] : 0;
		int d = f;
		for (int u = t; u != s; u = prev[u])
			Min(d, cap[pree[u]]);
		f -= d, F += d, C += h[t] * d;
		assert(C >= 0);
		for (int u = t; u != s; u = prev[u]) {
			cap[pree[u]] -= d;
			cap[pree[u] ^ 1] += d;
		}
	} return pi(F, C);
}
}
using namespace Primal;
int main() {
	s = 1, t = n;
	pi ans = solve(s, t);
	cout <<  ans.fi << ' ' << ans.se;
}