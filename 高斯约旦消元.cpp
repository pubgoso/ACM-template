struct gauss_jordan {
  int n, m;
  //把矩阵搞成一个上三角的矩阵 然后倒着解
  double a[101][101], b[101];
  double ans[N];
  int f[N];
  void set(int _n, int _m) {
    n = _n;
    m = _m;
  }
  void gao() {
    for (int i = 1; i <= n; i++)f[i] = i;
    for (int i = 1; i <= n; i++) { //
      if (i > n)break;
      int v = i;
      for (int j = i; j <= n; j++) { //把绝对值大的放在上面
        if (fabs(a[f[j]][i]) > fabs(a[f[v]][i])) {
          v = j;
        }
      }
      swap(f[v], f[i]); //将绝对值较大的一组 放到上面
      for (int j = 1; j <= n; j++)if (i != j) {
          int dx = f[i], dy = f[j];
          double x = a[dy][i] / a[dx][i];
          for (int k = 1; k <= m; k++) {
            a[dy][k] -= x * a[dx][k];
          }
        }
    }
  }
  void get_ans() {
    for (int i = n; i >= 1; i--) {
      if (a[f[i]][i] == 0) {
        cout << "No Solution\n";
        return ;
      }
      ans[i] = a[f[i]][m] / a[f[i]][i];
    }
    for (int i = 1; i <= n; i++)cout << ans[i] << '\n';
    return ;
  }
} G;