#include <bits/stdc++.h>
typedef long long ll;
#define maxn 100100
#define debug(args...)// fprintf(stderr,args)
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pip pair<int,pii>
using namespace std;

vector<pii> L[maxn];

int dp[20][maxn];
int peso[20][maxn];
int prof[maxn];

inline void dfs(int v,int p,int w){

	debug("dfs %d\n",v);
	
	if(v)
		prof[v] = 1 + prof[p];

	if(v != 0){
		dp[0][v] = p;
		peso[0][v] = w;
		for(int i=1;i<20;i++){
			dp[i][v] = dp[i-1][dp[i-1][v]];
			peso[i][v] = peso[i-1][v] + peso[i-1][dp[i-1][v]];
		}
	}
	
	for(int i=0;i<L[v].size();i++)
		if(L[v][i].first != p)
			dfs(L[v][i].first,v,L[v][i].second);
			
}

inline int dist(int a,int b){
	
	if(prof[a] > prof[b])
		swap(a,b);
		
	int dh = prof[b]-prof[a];
	
	int ret = 0;
	
	for(int i=0;i<20;i++)
		if(dh & (1<<i)){
			ret += peso[i][b];
			b = dp[i][b];
		}
		
	if(a == b)
		return ret;
	
	for(int i=19;i>=0;i--)
		if(dp[i][a] != dp[i][b]){
			ret += peso[i][a] + peso[i][b];
			a = dp[i][a];
			b = dp[i][b];
		}
	
	return ret + peso[0][a] + peso[0][b];
	
}

int block[maxn];

int size[maxn];

inline int dfs2(int v,int p){
	
	if(block[v])
		return 0;
	
	size[v] = 1;
	
	for(int i=0;i<L[v].size();i++)
		if(L[v][i].first != p){
			size[v] += dfs2(L[v][i].first,v);
		}
	
	return size[v];
	
}

int dad[maxn];

inline void go(int v,int pai){

	debug("go %d\n",v);
	int tot = dfs2(v,v);

	int o = v;
	int p = o;
	while(1){
		int ok = 1;
		for(int i=0;i<L[o].size();i++)
			if(L[o][i].first != p && !block[L[o][i].first]){
				if(size[L[o][i].first] > tot/2){
					ok = 0;
					p = o;
					o = L[o][i].first;
				}
			}
		if(ok) break;
	}
	
	debug("o = %d\n",o);
	dad[o] = pai;
	debug("dad[%d] = %d\n",o,pai);
	
	block[o] = 1;
	
	for(int i=0;i<L[o].size();i++)
		if(!block[L[o][i].first])
			go(L[o][i].first,o);
			
}

pii ans; // time / color

vector<pip> upd[maxn]; // dist // time / color

int cur = 0;

inline void update(int at,int v,int d,int c){

	int D = d - dist(at,v);
	debug("upd %d (d %d)\n",at,D);
	
	if(D < 0){
		if(dad[at] == -1) return;
		update(dad[at],v,d,c);
		return;
	}

	while(upd[at].size() >= 1 && upd[at][upd[at].size()-1].first < D)
		upd[at].pop_back();
	
	upd[at].pb(pip(D,pii(cur,c)));
	cur++;
	
	if(dad[at] == -1) return;
	update(dad[at],v,d,c);

}

inline void query(int at,int v){

	int D = dist(at,v);
	
	debug("query %d (d %d)\n",at,D);

	if(upd[at].size() >= 1 && upd[at][0].first >= D){
	
		int low = 0, up = upd[at].size()-1;
		
		while(low != up){
			int mid = (low+up+1)/2;
			if(upd[at][mid].first >= D)
				low = mid;
			else
				up = mid-1;	
		}
	
		if(upd[at][low].second.first > ans.first)
			ans = upd[at][low].second;	
				
	}
	
	if(dad[at] == -1) return;
	query(dad[at],v);

}

int ret;
char ch;
inline int read(){
	ret = 0;
	while((ch=getchar_unlocked()) >= '0'){
		ret = 10*ret + ch-'0';
	}
	return ret;
}

main(){
	
	int n = read();
	
	for(int i=0;i<n-1;i++){
		int a,b,p;
		a = read()-1;
		b = read()-1;
		p = read();
		L[a].pb(pii(b,p));
		L[b].pb(pii(a,p));
	}
	
	dfs(0,0,0);
	go(0,-1);
	
	int q = read();
	
	while(q--){
		int t=read();
		
		if(t == 1){
			int d,c,v;
			v = read()-1;
			d = read();
			c = read();
			update(v,v,d,c);
		}
		else {
			int v;
			v = read()-1;
			ans = pii(-1,0);
			query(v,v);
			printf("%d\n",ans.second);
		}
	}
	
}
	
