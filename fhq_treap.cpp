mt19937 mt(time(0));
struct fhq_treap {
	struct uzi {
		int l, r, val;
		int key, sz;
	} p[N];
	int root, cnt;

	int add_node(int val) {
		++cnt;
		p[cnt].l = p[cnt].r = 0;
		p[cnt].sz = 1;
		p[cnt].val = val;
		p[cnt].key = mt();
		return cnt;
	}
	void up(int x) {
		p[x].sz = p[p[x].l].sz + p[p[x].r].sz + 1;
	}
	void split(int now, int val, int &x, int &y) { //按值分裂
		if (!now)x = 0, y = 0;
		else {
			if (p[now].val <= val) { //那 左子树 必然全是x的 右子树 有的是 x 有的是 y
				x = now;
				split(p[now].r, val, p[x].r, y);
			} else {
				y = now;
				split(p[now].l, val, x, p[y].l);
			}
			up(now);
		}
	}
	int x, y, z, q;
	int merge(int l, int r) {
		if (!l || !r)return l + r;
		if (p[l].key > p[r].key) {
			p[l].r = merge(p[l].r, r);
			up(l);
			return l;
		} else {
			p[r].l = merge(l, p[r].l);
			up(r);
			return r;
		}
	}
	void add(int val) {
		int now = add_node(val);
		split(root, val, x, y);
		root = merge(merge(x, now), y);
	}
	void del(int val) {
		split(root, val, x, y);
		split(x, val - 1, q, z);
		root = merge(q, merge(p[z].l, p[z].r));
		root = merge(root, y);
	}
	void get_rank(int val) {
		split(root, val - 1, x, y);
		cout << p[x].sz + 1 << '\n';
		root = merge(x, y);
	}
	void get_num(int val) {
		int now = root;
		while (val) {
			if (p[p[now].l].sz + 1 == val)break;
			if (p[p[now].l].sz >= val) {
				now = p[now].l;
			} else if (p[p[now].l].sz + 1 < val) {
				val -= p[p[now].l].sz + 1;
				now = p[now].r;
			}
		}
		cout << p[now].val << '\n';
	}
	void get_pre(int val) {
		split(root, val - 1, x, y);
		int now = x;
		while (p[now].r)now = p[now].r;
		cout << p[now].val << '\n';
		root = merge(x, y);
	}
	void get_nxt(int val) {
		split(root, val, x, y);
		int now = y;
		while (p[now].l)now = p[now].l;
		cout << p[now].val << '\n';
		root = merge(x, y);
	}
};