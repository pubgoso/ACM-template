
struct DP_DS{
  #define mid (l+r>>1)
  const int N = ;
  const LL MX=1e18;
  struct uzi{
    LL mn,tag;
    uzi *ls,*rs;
  };
  vector<uzi*>res;
  uzi * new_node(){
    auto tmp=new uzi;
    res.pb(tmp);
    tmp->mn=MX;
    tmp->tag=0;
    tmp->ls=tmp->rs=NULL;
    return tmp;
  }
  void push_up(uzi * o){
    LL res=MX;
    if(o->ls!=NULL)res=min(res,o->ls->mn);
    if(o->rs!=NULL)res=min(res,o->rs->mn);
    o->mn=res;
  }
  void add(uzi *o,LL val){
    o->tag+=val;
    o->mn+=val;
  }
  void push_down(uzi *o){
    if(o->tag){
      if(o->ls!=NULL)add(o->ls,o->tag);
      if(o->rs!=NULL)add(o->rs,o->tag);
      o->tag=0;
    }
  }
  void up(uzi * &o,int l,int r,int x,LL y){
    if(o==NULL)o=new_node();
    if(l==r){
      o->mn=y;
      return;
    }
    push_down(o);
    if(x<=mid)up(o->ls,l,mid,x,y);
    else up(o->rs,mid+1,r,x,y);
    push_up(o);
  }
  LL get(uzi *o,int l,int r,int x){
    if(o==NULL)return MX;
    if(l==r){
      return o->mn;
    }
    push_down(o);
    if(x<=mid)return get(o->ls,l,mid,x);
    else return get(o->rs,mid+1,r,x);
  }
  uzi * merge(uzi *x,uzi *y){
    if(x==NULL)return y;
    if(y==NULL)return x;
    x->mn=min(x->mn,y->mn);
    push_down(x);
    push_down(y);
    x->ls=merge(x->ls,y->ls);
    x->rs=merge(x->rs,y->rs);
    return x;
  }
  void clear(){
    for(auto k:res){
      delete k;
    }
    res.clear();
  }
  #undef mid
  
};
