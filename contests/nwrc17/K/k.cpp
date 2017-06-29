#include <bits/stdc++.h>
using namespace std;

long double p[25];

main(){
	
	int k,r;
	cin >> k >> r;
	r = (1 << k) - r + 1;
	
	for(int i=1;i<=k;i++){
		
		int N = (1<<k)-1;
		int t = (1<<i)-1;
		
		p[i] = 1;
		for(int j=1;j<=t;j++)
			p[i] *= (long double) (r-j) / (N-j+1);
			
	}
	
	p[k+1] = 0;
	
	long double ans = 0;
	
	for(int i=1;i<=k;i++)
		ans += (long double) i * (p[i] - p[i+1]);
		
	printf("%.5f\n", (double) ans);
	
}
