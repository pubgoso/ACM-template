int n, m, k;
vector<pair<int, int>>v[N];
/*以i为根的子树 包含集合j的所有点的最小花费
从小到大枚举状态 ，然后dij增广
*/
int a[N], dp[N][1 << 10];
int vis[N];
priority_queue<pair<LL, int> >Q;
void dij(int i) {
  memset(vis, 0, sizeof vis);
  while (!Q.empty()) {
    auto x = Q.top();
    Q.pop();
    if (vis[x.se])continue;
    vis[x.se] = 1;
    for (auto kr : v[x.se]) {
      if (dp[kr.fi][i] > dp[x.se][i] + kr.se) {
        dp[kr.fi][i] = dp[x.se][i] + kr.se;
        Q.push({ -dp[kr.fi][i], kr.fi});
      }
    }
  }
}
int solve() {
  memset(dp, 0x3f3f3f, sizeof dp);
  const int mx = dp[0][0];
  for (int i = 1; i <= n; i++)dp[i][0] = 0;
  for (int i = 1; i <= k; i++) {
    cin >> a[i];
    dp[a[i]][1 << i - 1] = 0;
  }
  for (int i = 1; i < 1 << k; i++) {
    for (int j = 1; j <= n; j++) {
      for (int kr = i & (i - 1); kr; kr = i & (kr - 1)) {
        dp[j][i] = min(dp[j][kr] + dp[j][i ^ kr], dp[j][i]);
      }
      if (dp[j][i] < mx)Q.push({ -dp[j][i], j});
    }
    dij(i);
  }
  int ans = INT32_MAX;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, dp[i][(1 << k) - 1]);
  }
  return ans;
}