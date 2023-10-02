// SPOJ QTREE - AC
// http://www.spoj.com/problems/QTREE/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)(x).size())
using namespace std;
typedef long long ll;

#define oper max
#define NEUT -(1<<30)
struct STree{
	vector<int> t; int n;
	STree(int n):n(n),t(2*n+5,NEUT){}
	void upd(int p, int v){
		p+=n;
		for(t[p]=v;p>1;p>>=1) t[p>>1]=oper(t[p],t[p^1]);
	}
	int query(int l, int r){ // [l, r)
		int res=NEUT;
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){
			if(l&1) res=oper(res,t[l++]);
			if(r&1) res=oper(res,t[--r]);
		}
		return res;
	}
};


#define MAXN 100005

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
		r=oper(r,rmq.query(pos[x]+1,pos[y]+1));
		return r;
	}
	void upd(int x, int v){rmq.upd(pos[x],v);}
};
// queries on edges: - assign values of edges to "child" node
//                   - change pos[x] to pos[x]+1 in query (line 34)

int n;
int a[MAXN],b[MAXN],c[MAXN];

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%d",&n);
		vector<vector<int>> g(n);
		fore(i,0,n-1){
			scanf("%d%d%d",a+i,b+i,c+i);a[i]--;b[i]--;
			g[a[i]].pb(b[i]);g[b[i]].pb(a[i]);
		}
		HLD hld(g);
		fore(i,0,n-1){
			int x=a[i],y=b[i];
			if(x==hld.dad[y])hld.upd(y,c[i]);
			else hld.upd(x,c[i]);
		}
		char t[16];
		while(scanf("%s",t),t[0]!='D'){
			int i,j;
			scanf("%d%d",&i,&j);
			if(t[0]=='C'){
				int x=a[i-1],y=b[i-1];
				if(x==hld.dad[y])hld.upd(y,j);
				else hld.upd(x,j);
			}
			else printf("%d\n",hld.query(i-1,j-1));
		}
	}
	return 0;
}
