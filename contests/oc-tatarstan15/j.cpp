#include <bits/stdc++.h>
typedef long long ll;
#define maxn 1001000
#define debug(args...) //fprintf(stderr,args)
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
using namespace std;

ll exp(int a,int b,int mod){
	if(b == 0)
		return 1;
	ll ret = exp(a,b/2,mod);
	ret = (ret*ret)%mod;
	if(b%2)
		ret = (ret*a)%mod;
	return ret;
}

int phi[maxn];

pll crt(int a1,int m1,int a2,int m2){

	debug("phi[%d] = %d\n",m2,phi[m2]);
	ll a = (ll)(a2-a1) * exp(m1,phi[m2],m1*m2);
	a += a1;
	a %= m1*m2;
	if(a < 0)
		a += m1*m2;
		
	debug("md := %d\n",m1*m2);
		
	return pll(a,m1*m2);

}

ll inv(ll a,int mod){
	
	debug("phi[%d] = %d\n",mod,phi[mod]);
	return exp(a%mod,phi[mod]-1,mod);

}

ll pref[maxn];

ll fat(ll n,int mod){

	if(n == 0)
		return 1;
		
	ll ret = fat(n/mod,mod);
	
	ret = (ret * pref[n%mod]) % mod;
	
	ret = (ret * exp(pref[mod-1],n/mod,mod)) % mod;
	
	return ret;

}



main(){
	
	ll n, k, m;
	scanf("%lld%lld%lld",&n,&k,&m);
	
	int md = m;
	vector<pii> fact;
	
	for(int i=2;i*i<=m;i++)
		if(m%i == 0){
			int u = 0;
			int y = 1;
			while(m%i == 0){
				m /= i;
				y *= i;
				u++;
			}
			phi[y] = (y/i) * (i-1);
			fact.pb(pii(i,u));
		}
		
	if(m != 1){
		phi[m] = m-1;
		fact.pb(pii(m,1));
	}
	
	pll ans (0,1);
	
	for(int i=0;i<fact.size();i++){
		
		ll pot = 0;
		
		int p = fact[i].first;
		int t = fact[i].second;
		
		debug("%d^%d\n",p,t);
		
		ll cur = p;
		while(1){
			pot += n / cur;
			pot -= (n-k) / cur;
			pot -= k / cur;
			if(log(cur) + log(p) > log(5) + 18.0 * log(10)) break;
			cur *= p;
		}
		
		debug("pot = %lld\n",pot);
		
		int num = 1;
		
		for(int j=0;j<t;j++)
			num *= p;
		
		pref[0] = 1;
		pref[1] = 1;
		for(int j=2;j<=num;j++){
			int jj = j;
			while(jj%p == 0) jj /= p;
			pref[j] = ((ll)pref[j-1] * jj) % num;
		}
		ll a = fat(n,num);
		debug("%lld! = %lld\n",n,a);
		ll b = fat(k,num);
		debug("%lld! = %lld\n",k,b);
		ll c = fat(n-k,num);
		debug("%lld! = %lld\n",n-k,c);
		debug("phi[%d] = %d\n",num,phi[num]);
		a = (a * inv(b,num)) % num;
		a = (a * inv(c,num)) % num;
		
		for(int j=0;j<pot;j++)
			a = (a * p) % num;
		
		debug("a = %lld\n",a);
		
		ans = crt(ans.first,ans.second,a,num);
		
	}
	assert(ans.second == md);
	ans.first %= md;
	if(ans.first < 0)
		ans.first += md;
	printf("%lld\n",ans.first);
	
}
