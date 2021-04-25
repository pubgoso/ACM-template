#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 5e5 + 10;
#define fi first
#define se second
#define pb push_back
int n, a[N], q;
inline int read() {
	int f = 1, x = 0; char ch;
	do {ch = getchar(); if (ch == '-')f = -1;} while (ch < '0' || ch > '9');
	do {x = x * 10 + ch - '0'; ch = getchar();} while (ch >= '0' && ch <= '9');
	return f * x;
}
int mx[N << 2], mn[N << 2]; //最大 最小
int laz[N << 2]; //区间加
int cn[N << 2], cm[N << 2]; //次大  次小
int cmx[N << 2], cmn[N << 2]; //最大值个数 最小值个数
LL t[N << 2];
#define mid (l+r>>1)
#define ls o<<1
#define rs o<<1|1
void push_up(int o, int l, int  r) {
	t[o] = t[ls] + t[rs];
	if (mx[ls] > mx[rs]) {
		mx[o] = mx[ls];
		cmx[o] = cmx[ls];
		cm[o] = max(cm[ls], mx[rs]);
	} else if (mx[ls] < mx[rs]) {
		mx[o] = mx[rs];
		cmx[o] = cmx[rs];
		cm[o] = max(cm[rs], mx[ls]);
	} else {
		mx[o] = mx[rs];
		cmx[o] = cmx[ls] + cmx[rs];
		cm[o] = max(cm[ls], cm[rs]);
	}
	if (mn[ls] < mn[rs]) {
		mn[o] = mn[ls];
		cmn[o] = cmn[ls];
		cn[o] = min(cn[ls], mn[rs]);
	} else if (mn[ls] > mn[rs]) {
		mn[o] = mn[rs];
		cmn[o] = cmn[rs];
		cn[o] = min(cn[rs], mn[ls]);
	} else {
		mn[o] = mn[rs];
		cmn[o] = cmn[ls] + cmn[rs];
		cn[o] = min(cn[ls], cn[rs]);
	}
	return ;
}
void build(int o, int l, int r) {
	if (l == r) {
		mx[o] = mn[o] = a[l];
		laz[o] = 0;
		cm[o] = -1e9; cn[o] = 1e9;
		cmx[o] = cmn[o] = 1;
		t[o] = a[l];
		return ;
	}
	build(ls, l, mid);
	build(rs, mid + 1, r);
	push_up(o, l, r);
}
void push_tag(int o, int l, int r, LL d) {
	laz[o] += d; t[o] += 1ll * d * (r - l + 1);
	mx[o] += d; mn[o] += d;
	cn[o] += d; cm[o] += d;
	return ;
}
void turn_max(int o, int l, int r, int d) {
	t[o] += 1ll * cmn[o] * (d - mn[o]);
	mn[o] = d; mx[o] = max(d, mx[o]);
	if (mn[o] == mx[o]) {
		t[o] = 1ll * (r - l + 1) * d;
		cmn[o] = cmx[o] = r - l + 1;
		cm[o] = -1e9; cn[o] = 1e9;
	} else cm[o] = max(cm[o], d);
}
void turn_min(int  o, int l, int r, int d) {
	t[o] -= 1ll * cmx[o] * (mx[o] - d);
	mx[o] = d; mn[o] = min(mn[o], d);
	if (mn[o] == mx[o]) {
		t[o] = 1ll * (r - l + 1) * d;
		cmn[o] = cmx[o] = r - l + 1;
		cm[o] = -1e9; cn[o] = 1e9;
	} else {
		cn[o] = min(cn[o], d);
	}
}
void push_down(int o, int l, int r) {
	if (laz[o]) {
		push_tag(ls, l, mid, laz[o]);
		push_tag(rs, mid + 1, r, laz[o]);
		laz[o] = 0;
	}
	if (mx[ls] > mx[o] && cm[ls] < mx[o])turn_min(ls, l, mid, mx[o]);
	if (mx[rs] > mx[o] && cm[rs] < mx[o])turn_min(rs, mid + 1, r, mx[o]);
	if (mn[ls] < mn[o] && cn[ls] > mn[o])turn_max(ls, l, mid, mn[o]);
	if (mn[rs] < mn[o] && cn[rs] > mn[o])turn_max(rs, mid + 1, r, mn[o]);
}
void add(int o, int l, int r, int x, int y, LL d) {
	if (l >= x && r <= y) {
		push_tag(o, l, r, d);
		return ;
	}
	push_down(o, l, r);
	if (x <= mid)add(ls, l, mid, x, y, d);
	if (y > mid)add(rs, mid + 1, r, x, y, d);
	push_up(o, l, r);
}
void bemax(int o, int l, int r, int x, int y, LL d) {
	if (d <= mn[o])return ;
	if (l >= x && r <= y) {
		if (d < cn[o]) {
			turn_max(o, l, r, d);
			return ;
		}
	}
	push_down(o, l, r);
	if (x <= mid)bemax(ls, l, mid, x, y, d);
	if (y > mid)bemax(rs, mid + 1, r, x, y, d);
	push_up(o, l, r);
}
void bemin(int o, int l, int r, int x, int y, LL d) {
	if (mx[o] <= d)return ;
	if (l >= x && r <= y) {
		if (cm[o] < d) {
			turn_min(o, l, r, d);
			return ;
		}
	}
	push_down(o, l, r);
	if (x <= mid)bemin(ls, l, mid, x, y, d);
	if (y > mid)bemin(rs, mid + 1, r, x, y, d);
	push_up(o, l, r);
}
LL getsum(int o, int l, int r, int x, int y) {
	if (l >= x && r <= y)return t[o];
	LL ans = 0;
	push_down(o, l, r);
	if (x <= mid)ans += getsum(ls, l, mid, x, y);
	if (y > mid)ans += getsum(rs, mid + 1, r, x, y);
	return ans;
}
int getmax(int o, int l, int r, int x, int y) {
	if (l >= x && r <= y)return mx[o];
	int ans = -1e9;
	push_down(o, l, r);
	if (x <= mid)ans = max(getmax(ls, l, mid, x, y), ans);
	if (y > mid)ans = max(getmax(rs, mid + 1, r, x, y), ans);
	return ans;
}
int getmin(int o, int l, int r, int x, int y) {
	if (l >= x && r <= y)return mn[o];
	int ans = 1e9;
	push_down(o, l, r);
	if (x <= mid)ans = min(getmin(ls, l, mid, x, y), ans);
	if (y > mid)ans = min(getmin(rs, mid + 1, r, x, y), ans);
	return ans;
}
int main() {
	n = read();
	for (int i = 1; i <= n; i++)a[i] = read();
	build(1, 1, n);
	q = read();
	for (int i = 1; i <= q; i++) {
		int o, l, r, x;
		o = read(); l = read(); r = read();
		if (o == 1) {
			x = read();
			add(1, 1, n, l, r, x); //区间加
		} else if (o == 2) {
			x = read();
			bemax(1, 1, n, l, r, x); //区间 max
		} else if (o == 3) {
			x = read();
			bemin(1, 1, n, l, r, x); //区间 min
		} else if (o == 4) {
			printf("%lld\n", getsum(1, 1, n, l, r)); //区间 求和
		} else if (o == 5) {
			printf("%d\n", getmax(1, 1, n, l, r)); //区间最大值
		} else {
			printf("%d\n", getmin(1, 1, n, l, r)); //区间最小值
		}
	}
	return 0;
}