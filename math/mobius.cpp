// mu[x] = 0 if x has a squared prime else (-1)^(number of different primes of x)
short mu[MAXN] = {0,1};
void mobius(){ // O(n*log(n))
	fore(i,1,MAXN)if(mu[i])for(int j=i+i;j<MAXN;j+=i)mu[j]-=mu[i];
}
