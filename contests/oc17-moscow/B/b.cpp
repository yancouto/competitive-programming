#include <bits/stdc++.h>
using namespace std;

int pr(int a){
	for(int i=2;i*i<=a;i++)
		if(a%i == 0)
			return i;
	return a;
}

int f[1001000];

main(){
	srand(0);
	int n;
	scanf("%d",&n);
	int s = 0, ms = 0, Ms = 0;
	
	for(int i=1;i<=n;i++){
		
		if(i == 1)
			f[i] = 1;
		else if(pr(i) == i){
			if(rand()%2)
				f[i] = 1;
			else
				f[i] = -1;
		}
		else {
			f[i] = f[pr(i)] * f[i/pr(i)];
		}
		
		s += f[i];
		
		ms = min(ms,s);
		Ms = max(Ms,s);
		
		if(abs(s) > 20){
			printf("bad %d\n",i);
			break;
		}
			
	printf("%d %d\n",ms,Ms);
		
		printf("%d ",f[i]);		
	}
	
}
