struct KMP{
  int ne[N];
  void get_ne(char *p){
    int n=strlen(p);
    ne[0]=-1;
    for(int i=1;i<n;i++){
      int j=ne[i-1];
      while(j>=0 &&p[j+1]!=p[i]){
        j=ne[j];
      }
      if(p[j+1]==p[i])j++;
      ne[i]=j;
    }
  }
  int kmp(char * t,char *p){
    int n=strlen(t);
    int m=strlen(p);
    int match=-1;
    for(int i=0;i<n;i++){
      while(match>=0 && t[i]!=p[match+1])match=ne[match];
      if(t[i]==p[match+1]){
        match++;
        if(match==m-1)return i-match;
      }
    }
    return -1;
  }
}g;