struct hash_table {
	unsigned long long  seed, p;
	unsigned long long Hash[N], tmp[N];
	void set(LL _seed) {
		seed = _seed;
	}
	void work(char *s, int n) {
		tmp[0] = 1;
		Hash[0] = 0;
		for (int i = 1; i <= n; i++) {
			tmp[i] = tmp[i - 1] * seed;
			Hash[i] = (Hash[i - 1] * seed + (unsigned long long )(s[i])); //may need change
		}
	}
	unsigned long long get(int l, int r) {
		return ((Hash[r] - Hash[l - 1] * tmp[r - l + 1]));
	}
} g;