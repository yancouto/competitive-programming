#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <utility>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>

#define inf 1000000007
#define pii pair<int,int>
#define pip pair<int,pii>
#define pll pair<long long,long long>
#define pif pair<int,double>
#define eps 1e-7

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) fprintf(stderr,args)
#endif

#define pb push_back
#define maxn 1010

#define pdi pair<double,int>

typedef long long ll;
using namespace std;

int u;
int f = 0;

struct cara {
	vector<double> v;
	int idx;
	double dif;
	bool operator<(cara comp){
		if(f == 0)return v[u] < comp.v[u];
		return dif < comp.dif;
	}
	
}

v[maxn];


int ans[maxn];

double P[12];
double Pr[12];
double PP[12];

int score[12];

main(){
	
	freopen("genome.in","r",stdin);
	freopen("genome.out","w",stdout);
	int n,m;
	scanf("%d%d",&n,&m);
	
	for(int i=0;i<n;i++){
		v[i].v.clear();
		double best = -1;
		int qual = 0;
		v[i].idx = i;
		for(int j=0;j<m;j++){
			double a;
			scanf("%lf",&a);
			v[i].v.pb(a);
			if(a > best){
				best = a;
				qual = j;
			}
		}
		score[qual]++;
	}
	
	 u = 0;
	for(int i=1;i<m;i++)
		if(score[i] > score[u])
			u = i;
			
	debug("u - %d\n",u);
	
	sort(v,v+n);
	
	double part = (v[(int)(0.25*n)].v[u] + v[(int)(0.525*n)].v[u])/2;
	
	int r0 = 0;
	while(v[r0].v[u] < part) {
		for(int i=0;i<m;i++)
			P[i] += v[r0].v[i];
		ans[v[r0].idx] = 0;
		r0++;
	}
	
	for(int i=0;i<m;i++)
		P[i] /= r0;
	
	for(int i=0;i<m;i++)
		if(i != u){
			Pr[i] = Pr[i] / (1.0-P[u]);
		}
	
	vector<pdi> vv;
	
	for(int i=0;i<m;i++)
		vv.pb(pdi(P[i],i));
	
	sort(vv.begin(), vv.end());
	
	int A = vv[0].second, B = vv[0].second;
	
	for(int i=r0;i<n;i++){
		
		
		for(int j=0;j<m;j++)
			PP[j] = v[i].v[j] / (1.0-v[i].v[u]);
			
		v[i].dif = P[A] + P[B] - PP[A] - PP[B];
		
	}
	
	f = 1;
	sort(v+r0,v+n);
	
	for(int i=r0;i<r0+(n-r0)/2;i++)
		ans[v[i].idx] = 2;
	for(int i=r0+(n-r0)/2;i<n;i++)
		ans[v[i].idx] = 1;
		
	for(int i=0;i<n;i++)
		printf("%d\n",ans[i]);
		
}
