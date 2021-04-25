int L[N * 30], R[N * 30], fa[N * 30], dep[N * 30];
int root[N * 30];
namespace Persistant_Union_Set {
#define Mid ((l+r)>>1)
#define lson L[rt],l,Mid
#define rson R[rt],Mid+1,r
int cnt;
int n, m;

void build(int &rt, int l, int r) {
	rt = ++cnt;
	if (l == r) {fa[rt] = l; return ;}
	build(lson); build(rson);
}

void merge(int last, int &rt, int l, int r, int pos, int Fa) {
	rt = ++cnt; L[rt] = L[last], R[rt] = R[last];
	if (l == r) {
		fa[rt] = Fa;
		dep[rt] = dep[last];
		return ;
	}
	if (pos <= Mid)merge(L[last], lson, pos, Fa);
	else merge(R[last], rson, pos, Fa);
}

void update(int rt, int l, int r, int pos) {
	if (l == r) {dep[rt]++; return ;}
	if (pos <= Mid)update(lson, pos);
	else update(rson, pos);
}
int query(int rt, int l, int r, int pos) {
	if (l == r)return rt;
	if (pos <= Mid)return query(lson, pos);
	else return query(rson, pos);
}
int find(int rt, int pos) {
	int now = query(rt, 1, n, pos);
	if (fa[now] == pos)return now;
	return find(rt, fa[now]);
}
void _union(int i, int x, int y) {
	static int posx, posy;
	root[i] = root[i - 1];
	posx = find(root[i], x); posy = find(root[i], y);
	if (fa[posx] != fa[posy]){
		if (dep[posx] > dep[posy])swap(posx, posy);
		merge(root[i - 1], root[i], 1, n, fa[posx], fa[posy]);
		if (dep[posx] == dep[posy])update(root[i], 1, n, fa[posy]);
	}
}
#undef Mid
#undef lson
#undef rson
}
using namespace Persistant_Union_Set;

/*
build(root[0],1,n);
_union(i,l,r);
find(root[mid],x)
*/