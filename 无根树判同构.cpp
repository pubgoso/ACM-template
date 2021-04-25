vector<int>v[N];
struct tree_hash {
  int pr[N], ar[N], _cnt;
  unsigned long long H[N];
  unsigned int Ha[N];
  long long Hb[N];
  long long seed = 98243;
  const LL mod = 998244353;
  int sz[N];
  void PP() {
    for (int i = 2; i < N; i++) {
      if (!pr[i])ar[++_cnt] = i;
      for (int j = 1; j <= _cnt && 1ll * ar[j]*i < N; j++) {
        pr[ar[j]*i] = 1;
        if (i % ar[j] == 0)break;
      }
    }
  }
  void check(int x, int y) {
    sz[x] = 1;
    H[x] = 1;
    Ha[x] = 1;
    Hb[x] = 1;
    if (v[x].size() == 1) {
      return;
    }
    for (auto k : v[x]) {
      if (k == y)continue;
      check(k, x);
      sz[x] += sz[k];
    }
    for (auto k : v[x]) {
      if (k == y)continue;
      H[x] += H[k] * ar[sz[k]];
      Ha[x] += Ha[k] * ar[sz[k]];
      Hb[x] += Hb[k] * seed % mod;
      Hb[x] %= mod;
    }
  }
} G;
int n;
int sz[N], son[N], rt, tr;
void root(int now, int pre) { //æ�¾é��å¿�
  sz[now] = 1;
  son[now] = 0;
  for (auto k : v[now]) {
    if ( k == pre)continue;
    root(k, now);
    sz[now] += sz[k];
    son[now] = max(son[now], sz[k]);
  }
  son[now] = max(son[now], n - sz[now]);
  if (!rt || son[rt] > son[now]) {
    rt = now;
    tr = 0;
  } else if (rt && son[rt] == son[now]) {
    tr = now;
  }
  return ;
}
int check() {
  for (int i = 1; i <= n; i++)v[i].clear();
  for (int i = 1; i < n; i++) { //输入两棵树
    int s, t;
    cin >> s >> t;
    v[s].pb(t);
    v[t].pb(s);
  }
  root(1, 0);
  G.check(rt, 0);
  vector<pair<unsigned long long, pair<unsigned int, long long> >>vv, ww;
  vv.pb({G.H[rt], {G.Ha[rt], G.Hb[rt]}});
  if (tr) {
    G.check(tr, 0);
    vv.pb({G.H[tr], {G.Ha[tr], G.Hb[tr]}});
  }
  for (int i = 1; i <= n; i++)v[i].clear();
  for (int i = 1; i < n; i++) {
    int s, t;
    cin >> s >> t;
    v[s].pb(t);
    v[t].pb(s);
  }
  rt = 0; tr = 0;
  root(1, 0);
  G.check(rt, 0);
  ww.pb({G.H[rt], {G.Ha[rt], G.Hb[rt]}});
  if (tr) {
    G.check(tr, 0);
    ww.pb({G.H[tr], {G.Ha[tr], G.Hb[tr]}});
  }
  int st = 0;
  for (auto x : vv) {
    for (auto y : ww) {
      if (x.fi == y.fi && x.se == y.se) {
        st = 1;
        break;
      }
    }
  }
  return st;
}