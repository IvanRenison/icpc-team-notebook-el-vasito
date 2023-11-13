struct SuffixAuto {
	struct state {int len,link;map<char,int> next;};
	vector<state> st={{0,-1,{}}}; // You can preallocate 2*MAXN+1
	int last=0;
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
//  input: abcbcbc
//  i,link,len,next
//  0 -1 0 (a,1) (b,5) (c,7)
//  1 0 1 (b,2)
//  2 5 2 (c,3)
//  3 7 3 (b,4)
//  4 9 4 (c,6)
//  5 0 1 (c,7)
//  6 11 5 (b,8)
//  7 0 2 (b,9)
//  8 9 6 (c,10)
//  9 5 3 (c,11)
//  10 11 7
//  11 7 4 (b,8)
