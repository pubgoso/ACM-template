const int inf = 1e9;
struct uzi {
#define mid (l+r>>1)
#define ls o<<1
#define rs o<<1|1
	int t[N << 2], laz[N << 2];
	void build(int o, int l, int r) {
		laz[o] = t[o] = inf;
		if (l == r)return;
		build(ls, l, mid);
		build(rs, mid + 1, r);
	}
	void up(int o, int l, int r, int x, int y) {
		if (l == r) {
			t[o] = y;
			return ;
		}
		if (x <= mid)up(ls, l, mid, x, y);
		else up(rs, mid + 1, r, x, y);
		t[o] = min(t[ls], t[rs]);
	}
	int get(int o, int l, int r, int x, int y) {
		assert(x <= y);
		if (l >= x && r <= y)return t[o];
		int res = inf;
		if (x <= mid)res = min(res, get(ls, l, mid, x, y));
		if (y > mid)res = min(res, get(rs, mid + 1, r, x, y));
		return res;
	}
#undef mid
#undef ls
#undef rs
} dx, dy;