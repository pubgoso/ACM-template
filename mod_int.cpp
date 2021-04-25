const int mod=;
int add(int x,int y){
  x+=y;
  if(x>=mod)x-=mod;
  if(x<0)x+=mod;
  return x;
}
int mul(int x,int y){
  return 1ll*x*y%mod;
}
int powmod(int x,int y,int z=1){
  for(;y;y>>=1,x=mul(x,x))if(y&1)z=mul(z,x);
  return z;
}
int di(int x,int y){
  return mul(x,powmod(y,mod-2));
}