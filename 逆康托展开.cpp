void get(int *tmp,LL ti,int len){
  for(int i=1;i<=len;i++)tmp[i]=i,vis[i]=0;
  for(int i=len;i>=1;i--){
    int now=ti/fac[i-1],ten=now;
    for(int j=1;j<=len;j++){//可用线段树优化至log
      if(!vis[j]){
        if(!now){
          tmp[len-i+1]=j;
          vis[j]=1;
          break;
        }
        now--;
      }
    }
    ti-=ten*fac[i-1];
  }
}