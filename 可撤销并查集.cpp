int f[N],sz[N];
void init(int n){
  for(int i=1;i<=n;i++)f[i]=i,sz[i]=1;
}
int find(int x){
  while(x!=f[x]){
    x=f[x];
  }
  return x;
}
int st[N],tot;
void merge(int x,int y){
  int dx=find(x),dy=find(y);
  if(dx==dy)
    return;
  if(sz[dx]>sz[dy])swap(dx,dy);
  sz[dy]+=sz[dx];
  f[dx]=dy;
  st[++tot]=dx;
}
void roll_back(int y){
  while(tot>y){
    int now=st[tot--];
    sz[f[now]]-=sz[now];
    f[now]=now;
  }
}