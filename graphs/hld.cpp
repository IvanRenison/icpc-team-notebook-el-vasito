// Tree with values updates and path querys
struct HLD {
	vector<vector<int>> g;
	vector<int> wg,dad,dep, // weight,father,depth
							pos,head;
	int curpos;STree rmq;
	HLD(const vector<vector<int>>& g) : g(g), wg(SZ(g)), dad(SZ(g)),
			dep(SZ(g)), pos(SZ(g)), head(SZ(g)), rmq(SZ(g)) {
		dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);
	}
	void dfs1(int x){
		wg[x]=1;
		for(int y:g[x])if(y!=dad[x]){
			dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
			wg[x]+=wg[y];
		}
	}
	void hld(int x, int c){
		if(c<0)c=x;
		pos[x]=curpos++;head[x]=c;
		int mx=-1;
		for(int y:g[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
		if(mx>=0)hld(mx,c);
		for(int y:g[x])if(y!=mx&&y!=dad[x])hld(y,-1);
	}
	int query(int x, int y){
		int r=NEUT;
		while(head[x]!=head[y]){
			if(dep[head[x]]>dep[head[y]])swap(x,y);
			r=oper(r,rmq.query(pos[head[y]],pos[y]+1));
			y=dad[head[y]];
		}
		if(dep[x]>dep[y])swap(x,y); // now x is lca
		r=oper(r,rmq.query(pos[x],pos[y]+1));
		return r;
	}
	void upd(int x, int v){rmq.upd(pos[x],v);}
};
// queries on edges: - assign values of edges to "child" node
//                   - change pos[x] to pos[x]+1 in query (line 34)
