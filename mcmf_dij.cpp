struct mcmf{
	#define fi first
	#define se second
	#define INF   0x3f3f3f3f
	#undef fi
	#undef se
	#undef INF
	typedef long long ll;
	typedef pair<int,int> P;
	 
	constexpr int MAXN=1e6+10;
	 
	int n,m,s,t,sum,cnt,head[5010],level[5010],h[5010],pu[5010],pe[5010];
	 
	struct Edge{
	    int to,next,cap,cost;
	}edge[MAXN<<1];
	 
	void addedge(int u,int v,int cap,int cost){
	    edge[cnt].to=v;
	    edge[cnt].cap=cap;
	    edge[cnt].cost=cost;
	    edge[cnt].next=head[u];
	    head[u]=cnt++;
	    edge[cnt].to=u;
	    edge[cnt].cap=0;
	    edge[cnt].cost=-cost;
	    edge[cnt].next=head[v];
	    head[v]=cnt++;
	}
	 
	void init(){
	    sum=cnt=0;
	    for(int i=s;i<=t;i++)   head[i]=-1,h[i]=0;
	}
	 
	bool dijkstra(){
	    for(int i=s;i<=t;i++)   level[i]=INF;
	    priority_queue<P,vector<P>,greater<P> >q;
	    level[s]=0; q.push(P(0,s));
	    while(!q.empty()){
	        int u=q.top().se,val=q.top().fi;    q.pop();
	        if(level[u]<val)  continue;
	        for(int i=head[u];~i;i=edge[i].next){
	            int v=edge[i].to,w=edge[i].cost;
	            if(edge[i].cap>0&&level[v]>level[u]+w+h[u]-h[v]){
	                level[v]=level[u]+w+h[u]-h[v];
	                pu[v]=u,pe[v]=i;
	                q.push({level[v],v});
	            }
	        }
	    }
	    return level[t]!=INF;
	}
	 
	int Max_Flow(){
	    int flow=0,f;
	    while(dijkstra()){
	        f=INF;
	        for(int i=s;i<=t;i++)   h[i]+=(level[i]!=INF)? level[i]: 0;
	        for(int u=t;u!=s;u=pu[u])   f=min(f,edge[pe[u]].cap);
	        flow+=f,sum+=h[t]*f;
	        for(int u=t;u!=s;u=pu[u])   edge[pe[u]].cap-=f,edge[pe[u]^1].cap+=f;
	    }
	    return flow;
	}
	 
};