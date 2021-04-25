struct Gauss {
	int n, m;
	//把矩阵搞成一个上三角的矩阵 然后倒着解
	double a[N][N], b[N];
	//1-n [1-m-1 m]
	double ans[N];
	int f[N];
	void set(int _n, int _m) {
		n = _n;
		m = _m;
	}
	void gao() {
		for (int i = 1; i <= n; i++)f[i] = i;
		for (int i = 1; i <= m; i++) { //
			if (i > n)break;
			int v = i;
			for (int j = i; j <= n; j++) {
				if (fabs(a[f[j]][i]) > fabs(a[f[v]][i])) {
					v = j;
				}
			}
			swap(f[v], f[i]); //将绝对值较大的一组 放到上面
			for (int j = i + 1; j <= n; j++) {
				int dx = f[i], dy = f[j];
				double x = a[dy][i] / a[dx][i];
				for (int k = 1; k <= m; k++) {
					a[dy][k] -= x * a[dx][k];
				}
			}
		}
	}
	//搞完之后 不为0的行 为矩阵的秩
	void get_ans() {
		for (int i = n; i >= 1; i--) {
			double sum = 0;
			for (int j = 1; j < m; j++) {
				sum += a[f[i]][j];
			}
			if (sum == 0) { //最后一列不为0的时候 就是无解，为0就是有自由元
				cout << "No Solution\n";
				return;
			}
			for (int j = m - 1; j > i; j--) {
				a[f[i]][m] -= ans[j] * a[f[i]][j];
			}
			ans[i] = a[f[i]][m] / a[f[i]][i];
		}
		for (int i = 1; i <= n; i++)cout << ans[i] << '\n';
		return ;
	}
} G;