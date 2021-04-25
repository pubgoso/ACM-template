int a[N],cnt,p[N],mu[N];
LL phi[N];
void P(){
  phi[1]=mu[1]=1;
  for(int i=2;i<N;i++){
    if(!p[i])a[++cnt]=i,mu[i]=-1,phi[i]=i-1;
    for(int j=1;j<=cnt&&1ll*a[j]*i<N;j++){
      p[a[j]*i]=1;
      if(i%a[j]==0){
        mu[i*a[j]]=0;
        phi[i*a[j]]=a[j]*phi[i];
        break;
      }
      mu[a[j]*i]=-mu[i];
      phi[i*a[j]]=phi[i]*phi[a[j]];
    }
  }
  for(int i=2;i<N;i++) {
    mu[i] += mu[i - 1], phi[i] += phi[i - 1];
  }
}