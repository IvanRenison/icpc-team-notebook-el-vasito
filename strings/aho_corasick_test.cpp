// UVA 10679 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1620
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;

struct AhoCorasick {
	struct vertex {
		map<char,int> next,go;
		int p,link;
		char pch;
		vector<int> leaf;
		vertex(int p=-1, char pch=-1):p(p),link(-1),pch(pch){}
	};
	vector<vertex> t;
	AhoCorasick():t(1){}
	void add_string(string s, int id){
		int v=0;
		for(char c:s){
			if(!t[v].next.count(c)){
				t[v].next[c]=t.size();
				t.pb(vertex(v,c));
			}
			v=t[v].next[c];
		}
		t[v].leaf.pb(id);
	}
	int get_link(int v){
		if(t[v].link<0) {
			if(!v||!t[v].p)t[v].link=0;
			else t[v].link=go(get_link(t[v].p),t[v].pch);
		}
		return t[v].link;
	}
	int go(int v, char c){
		if(!t[v].go.count(c)) {
			if(t[v].next.count(c))t[v].go[c]=t[v].next[c];
			else t[v].go[c]=v==0?0:go(get_link(v),c);
		}
		return t[v].go[c];
	}
};

AhoCorasick ac;

bool r[1024];
bool vis[1<<20];

void proc(int x){
	if(x==-1||vis[x])return;
	vis[x]=true;
	fore(i,0,ac.t[x].leaf.size())r[ac.t[x].leaf[i]]=true;
	proc(ac.t[x].link);
}

char s[100005];
char tt[100005];
int n;

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		ac = AhoCorasick();
		scanf("%s%d",s,&n);
		fore(i,0,n){
			scanf("%s",tt);
			ac.add_string(string(tt),i);
		}
		int k=0;
		for(int i=0;s[i];++i){
			k=ac.go(k,s[i]);
			proc(k);
		}
		fore(i,0,n)puts(r[i]?"y":"n");
	}
	return 0;
}
