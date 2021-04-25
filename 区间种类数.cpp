inline void update(int &rt, int pre, int pos, int c, int l, int r) {
	if (l > pos || r < pos)return ;
	t[rt = ++tot] = t[pre];
	ls[rt] = ls[pre], rs[rt] = rs[pre];
	t[rt] += c;
	if (l == r) {
		return;
	}
	int m = (l + r) >> 1;
	if (pos <= m)update(ls[rt], ls[pre], pos, c, l, m);
	else update(rs[rt], rs[pre], pos, c, m + 1, r);
}
inline int get(int rt, int x, int y, int l, int r) {
	if (l >= x && r <= y)return t[rt];
	int m = l + r >> 1, z = 0;
	if (x <= m)z += get(ls[rt], x, y, l, m);
	if (y > m)z += get(rs[rt], x, y, m + 1, r);
	return z;
}
inline int ge(int rt, int l, int r, int k) {
	if (l == r)return l;
	int lss = t[ls[rt]];
	int mid = l + r >> 1;
	if (lss >= k)return ge(ls[rt], l, mid, k);
	else return ge(rs[rt], mid + 1, r, k - t[ls[rt]]);
}
/*
建树 根据不同情况 正着或反着建 （在主席树上二分 ）
for(int i=n;i>=1;i--){
  a[i]++;
  if(vis[a[i]]){
    int k=0;
    update(k,root[i+1],vis[a[i]],-1,1,n);
    update(root[i],k,i,1,1,n);
  }else{
    update(root[i],root[i+1],i,1,1,n);
  }
  vis[a[i]]=i;
}
*/

/*
查询
get(root[r],l,r,1,n);
get(root[l],l,r,1,n);
*/
//