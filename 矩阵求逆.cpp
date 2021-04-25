struct Matrix_inv {
  int n, a[N][N], d[N][N], f[N], sum[N][N], Z[N][N];
  int pm(int x, int y) {
    int z = 1;
    while (y) {
      if (y & 1)z = 1ll * z * x % mod;
      x = 1ll * x * x % mod;
      y >>= 1;
    }
    return z;
  }
  void set(int _n) {
    n = _n;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)d[i][j] = 0, sum[i][j] = 0, Z[i][j] = a[i][j];
    }
  }
  void gao() {
    for (int i = 1; i <= n; i++)f[i] = i, d[i][i] = 1;
    for (int i = 1; i <= n; i++) { //
      for (int j = 1; j <= n; j++)if (i != j) {
          int dx = f[i], dy = f[j];
          int x = 1ll * a[dy][i] * pm(a[dx][i], mod - 2) % mod;
          for (int k = 1; k <= n; k++) {
            a[dy][k] = (a[dy][k] - 1ll * x * a[dx][k] % mod + mod) % mod;
            d[dy][k] = (d[dy][k] - 1ll * x * d[dx][k] % mod + mod) % mod;
          }
        }
    }
  }
  void get_ans() {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        d[i][j] = 1ll * d[i][j] * pm(a[i][i], mod - 2) % mod;
      }
    }
    return ;
  }
  /*
  void check(){
    for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++){
        for(int k=1;k<=n;k++){
          sum[i][j]=(0ll+sum[i][j]+1ll*Z[i][k]*d[k][j]%mod+mod)%mod;
        }
        cout<<sum[i][j]<<' ';
      }
      cout<<'\n';
    }

  }
   */
} G;
// G.set()
//G.gao()
//G.getans()
//G.d 即为矩阵的逆