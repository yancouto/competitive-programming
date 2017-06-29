#include <bits/stdc++.h>
using namespace std;

int v[100100];

main(){
	
	int n,k,r;
	scanf("%d%d%d",&n,&k,&r);
	
	for(int i=0;i<k;i++){
		int a;
		scanf("%d",&a);
		v[a] = 1;
	}
	
	int s = 0;
	for(int i=1;i<=r;i++)
		s += v[i];
		
	int ans = 0;
		
	for(int i=r;i<=n;i++){
	
		//printf("i %d s %d\n",i,s);
		
		int p = i;
		while(s < 2){
			if(v[p]){
				p--;
				continue;
			}
			v[p] = 1;
			s++;
			//printf("+ %d\n",p);
			ans++;
			p--;
		}
		
		s -= v[i-r+1];
		s += v[i+1];
	
	}
	
	printf("%d\n",ans);
	
}
