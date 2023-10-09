// CSES Path Queries - AC
// https://cses.fi/problemset/task/1138/
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define fore(i,a,b) for(int i=a,gmat=b;i<gmat;i++)
#define SZ(x) ((int)x.size())
#define FIN ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
typedef long long ll;

#define oper(a, b) ((a)+(b))
#define NEUT 0
struct STree{
	vector<ll> t; int n;
	STree(int n):n(n),t(2*n+5,NEUT){}
	void upd(int p, ll v){
		p+=n;
		for(t[p]=v;p>1;p>>=1) t[p>>1]=oper(t[p],t[p^1]);
	}
	ll query(int l, int r){ // [l, r)
		ll res=NEUT;
		for(l+=n,r+=n;l<r;l>>=1,r>>=1){
			if(l&1) res=oper(res,t[l++]);
			if(r&1) res=oper(res,t[--r]);
		}
		return res;
	}
};

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
	ll query(int x, int y){
		ll r=NEUT;
		while(head[x]!=head[y]){
			if(dep[head[x]]>dep[head[y]])swap(x,y);
			r=oper(r,rmq.query(pos[head[y]],pos[y]+1));
			y=dad[head[y]];
		}
		if(dep[x]>dep[y])swap(x,y); // now x is lca
		r=oper(r,rmq.query(pos[x],pos[y]+1));
		return r;
	}
	void upd(int x, ll v){rmq.upd(pos[x],v);}
};
// queries on edges: - assign values of edges to "child" node
//                   - change pos[x] to pos[x]+1 in query (line 34)

int main(){FIN;

	int n, q;
	cin >> n >> q;
	vector<ll> vs(n);
	fore(i, 0, n) cin >> vs[i];
	vector<vector<int>> g(n);
	fore(i, 0, n - 1) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	HLD hld(g);
	fore(i, 0, n) hld.upd(i, vs[i]);
	while(q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int s; ll x;
			cin >> s >> x;
			s--;
			hld.upd(s, x);
		} else {
			int s;
			cin >> s;
			s--;
			cout << hld.query(0, s) << '\n';
		}
	}

	return 0;
}
