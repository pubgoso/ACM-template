int p[N],a[N],cnt;
void P(){
  mu[1]=1;
  for(int i=2;i<N;i++){
    if(!p[i])a[++cnt]=i,mu[i]=-1;
    for(int j=1;j<=cnt&&1ll*a[j]*i<N;j++){
      p[a[j]*i]=1;
      if(i%a[j]==0){
        mu[i*a[j]]=0;
        break;
      }
      mu[i*a[j]]=-mu[i];
    }
  }
  for(int i=2;i<N;i++)mu[i]+=mu[i-1];
}