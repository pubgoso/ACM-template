struct tree_intersect{
  vector<int>v[N], g[N];
  int dep[N], f[N][22],tin[N],tout[N];
  int n, dfn[N], CNT,r;
  void init(int _n, int _r) {
    n = _n; r = _r; CNT = 0;
    for (int i = 1; i <= n; i++) {
      v[i].clear();
      g[i].clear();
    }
  }
  int lca(int u, int v) {
    if (dep[u] < dep[v])swap(u, v);
    for (int i = 20; i >= 0; i--)if ((dep[u] - dep[v]) >> i & 1)u = f[u][i];
    if (u == v)return u;
    for (int i = 20; i >= 0; i--)if (f[u][i] != f[v][i])u = f[u][i], v = f[v][i];
    return f[u][0];
  }
  void dfs(int x, int y) {
    f[x][0] = y; dfn[x] = ++CNT;
    dep[x] = dep[y] + 1;
    tin[x]=++CNT;
    for (int j = 1; j <= 20; j++) {
      f[x][j] = f[f[x][j - 1]][j - 1];
    }
    for (auto k : v[x])if (k != y) {
        dfs(k, x);
      }
    tout[x]=CNT;
  }
  int is_parent(int par,int v){
    return tin[par] <= tin[v] && tout[v] <= tout[par];
  }
  int dis(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
  }
  pair<int,int> intersect (int a1, int b1, int a2, int b2) {
    if (a1 == -1 || a2 == -1) {
      return make_pair(-1, -1);
    }
    int lca1 = lca(a1, b1);
    int lca2 = lca(a2, b2);
    vector<int> nodes = {a1, b1, a2, b2, lca1, lca2, lca(a1, a2), lca(a1, b2), lca(b1, a2), lca(b1, b2)};
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    int best = -1e9;
    pair<int,int> ret = {-1, -1};

    auto is_ok = [&](int v) {
      return (is_parent(v, a1) || is_parent(v, b1)) && is_parent(lca1, v) && (is_parent(v, a2) || is_parent(v, b2)) && is_parent(lca2, v);
    };
    int sz=(int)nodes.size();
    for (int i = 0; i < sz; ++i) {
      for (int j = i; j < sz; ++j) {
        if (is_ok(nodes[i]) && is_ok(nodes[j])) {
          int val = dis(nodes[i], nodes[j]);
          if (val > best) {
            best = val;
            ret = {nodes[i], nodes[j]};
          }
        }
      }
    }
    return ret;
  }
} G;
