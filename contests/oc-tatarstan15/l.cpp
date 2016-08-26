#include <bits/stdc++.h>
typedef long long ll;
#define maxn 100100
#define debug
using namespace std;

int freq[maxn];

int maior;

int v[maxn];

main(){
	
	int n;
	scanf("%d",&n);
	
	multiset<int> s;
	
	for(int i=0;i<n;i++){
		scanf("%d",v+i);
		freq[v[i]]++;
		s.insert(v[i]);
	}	
	
	maior = *(--s.end());
	ll ans = (ll) maior * freq[maior];
	debug("%d * %d\n",maior,freq[maior]);
	
	for(int i=0;i<n-1;i++){
	
		if(v[i] == 0)
			continue;
		
		s.erase(s.find(v[i]));
		s.erase(s.find(v[i+1]));
		freq[v[i]]--;
		freq[v[i+1]]--;
		v[i]--;
		v[i+1]++;
		s.insert(v[i]);
		s.insert(v[i+1]);
		freq[v[i]]++;
		freq[v[i+1]]++;
		maior = *(--s.end());
		ans = min(ans, (ll) maior * freq[maior]);
		debug("i %d\n",i);
		debug("%d * %d\n",maior,freq[maior]);
		
		s.erase(s.find(v[i]));
		s.erase(s.find(v[i+1]));
		freq[v[i]]--;
		freq[v[i+1]]--;
		v[i]++;
		v[i+1]--;
		s.insert(v[i]);
		s.insert(v[i+1]);
		freq[v[i]]++;
		freq[v[i+1]]++;
	}
	
	for(int i=1;i<n;i++){
		
		if(v[i] == 0)
			continue;
		
		s.erase(s.find(v[i]));
		s.erase(s.find(v[i-1]));
		freq[v[i]]--;
		freq[v[i-1]]--;
		v[i]--;
		v[i-1]++;
		s.insert(v[i]);
		s.insert(v[i-1]);
		freq[v[i]]++;
		freq[v[i-1]]++;
		maior = *(--s.end());
		ans = min(ans, (ll) maior * freq[maior]);
		debug("i %d\n",i);
		debug("%d * %d\n",maior,freq[maior]);
		
		s.erase(s.find(v[i]));
		s.erase(s.find(v[i-1]));
		freq[v[i]]--;
		freq[v[i-1]]--;
		v[i]++;
		v[i-1]--;
		s.insert(v[i]);
		s.insert(v[i-1]);
		freq[v[i]]++;
		freq[v[i-1]]++;
	}
	
	printf("%lld\n",ans);
	
}
