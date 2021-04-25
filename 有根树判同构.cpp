struct tree_hash {//有根树的判定
	int pr[N], ar[N], _cnt;
	unsigned long long H[N];
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
	void check(int x) {
		sz[x] = 1; H[x] = 1;
		if (!v[x].size()) {
			H[x] = 1;
			return;
		}
		H[x] = 0;
		for (auto k : v[x]) {
			check(k);
			sz[x] += sz[k];
		}
		for (auto k : v[x]) {
			H[x] += H[k] * ar[sz[k]];
		}
		H[x] *= sz[x];
	}
};