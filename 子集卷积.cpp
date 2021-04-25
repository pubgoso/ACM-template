struct subset_conv {
	int add(int x) {
		if (x >= mod)x -= mod;
		if (x < 0)x += mod;
		return x;
	}
	int mul(int x, int y) {
		return 1ll * x * y % mod;
	}
	inline void fmt_or(vector<int>& A, int dmt = 1, int base = Base) {
		int len = 1 << base;
		for (int i = 1; i < len; i <<= 1)
			for (int j = 0, t = i << 1; j < len; j += t)
				for (int k = j, K = j + i; k < K; ++k) A[k + i] = add(A[k + i] + dmt * A[k]);
	}
	vector<int> pc;
	void get_top(int sz) {
		pc.resize(sz, 0);
		for (int i = 1; i < sz; ++i) pc[i] = pc[i >> 1] + (i & 1);
	}
	vector<int> subset_conv(vector<int> &A, vector<int>&B, int base) {
		int len = 1 << base;
		vector<int> H(len);
		vector<vector<int> > siga(base + 1, vector<int>(len, 0)), sigb = siga, sigh = siga;
		for (int S = 0; S < len; ++S) siga[pc[S]][S] = A[S], sigb[pc[S]][S] = B[S];
		for (int i = 0; i <= base; ++i) {
			fmt_or(siga[i], 1, base);
			fmt_or(sigb[i], 1, base);
			for (int S = 0; S < len; ++S)
				for (int j = 0; j <= i; ++j) sigh[i][S] = add(sigh[i][S] + mul(siga[j][S], sigb[i - j][S]));
			fmt_or(sigh[i], -1, base);
		}
		for (int S = 0; S < len; ++S) H[S] = sigh[pc[S]][S];
		return H;
	}
};
//ans_x  = \sum _{i|j=x and i&j=0} a_i*b_j
// len = 1<<Base
//get_top(len)
//A=subset_conv(A,B,Base)
//details :  ans[0]=1