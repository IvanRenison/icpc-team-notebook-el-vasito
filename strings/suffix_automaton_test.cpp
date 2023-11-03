// SPOJ SUBST1 - AC
// http://www.spoj.com/problems/SUBST1/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct SuffixAuto {
	struct state {int len,link;map<char,int> next;};
	vector<state> st; // You can preallocate 2*MAXN+1
	int last;
	SuffixAuto() {
		st.push_back({0,-1,{}});
		last=0;
	}
	void extend(char c){
		int k=st.size(),p;
		st.push_back({st[last].len+1,0,{}});
		for(p=last;p!=-1&&!st[p].next.count(c);p=st[p].link)st[p].next[c]=k;
		if(p!=-1){
			int q=st[p].next[c];
			if(st[p].len+1==st[q].len)st[k].link=q;
			else {
				int w=st.size();
				st.push_back({st[p].len+1,st[q].link,st[q].next});
				for(;p!=-1&&st[p].next[c]==q;p=st[p].link)st[p].next[c]=w;
				st[q].link=st[k].link=w;
			}
		}
		last=k;
	}
};

SuffixAuto sa;

ll dp[100005];

ll f(int x){
	if(dp[x]>=0)return dp[x];
	ll r=1;
	for(auto [_,i]:sa.st[x].next)r+=f(i);
	return dp[x]=r;
}

int main(){
	int tn;
	cin>>tn;
	while(tn--){
		string s;
		cin>>s;
		sa = SuffixAuto();
		sa.st.reserve(2*s.size()+1);
		for(char c:s)sa.extend(c);
		memset(dp,-1,sizeof(dp));
		cout<<f(0)-1<<'\n';
	}
	return 0;
}
