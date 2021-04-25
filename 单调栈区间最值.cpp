struct Max_stack {
  int q[N], l[N], r[N], cnt;
  void init(int *a, int n) {
    cnt = 0;
    for (int i = 1; i <= n; i++) {
      while (cnt && a[q[cnt]] <= a[i])cnt--;
      l[i] = q[cnt] + 1;
      q[++cnt] = i;
    }
    cnt = 0;
    for (int i = n; i >= 1; i--) {
      while (cnt && a[q[cnt]] <= a[i])cnt--;
      if (!cnt)r[i] = n;
      else r[i] = q[cnt] - 1;
      q[++cnt] = i;
    }
  }
} Ma;