#include <bits/stdc++.h>
#define pb push_back
#define pii pair<int,int>
using namespace std;

vector<pii> ans;

int N;

int go(int n,int a){

	if(n == 0)
		return 0;
	ans.pb(pii(a,a+N));
	if(n == 1)
		return 0;
	for(int i=a+1;i<a+n;i++){
		ans.pb(pii(a,i));
		ans.pb(pii(a+N,i+N));
	}
	go(n-2,a+1);
}

main(){
	
	int n;
	scanf("%d",&n);
	N = n;
	
	go(n,1);
	
	printf("%d\n",(int)ans.size());
	
	for(int i=0;i<ans.size();i++)
		printf("%d %d\n",ans[i].first,ans[i].second);
	
}
