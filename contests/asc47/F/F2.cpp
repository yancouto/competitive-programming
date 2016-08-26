#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 100009;

vector<int> adj[N];
int out[N];
set<int> c[N];

int go(int u, int o) {
	out[u]=  1;
	for(int v : adj[u])
		c[v].insert(o);
}

int main() {
	int i, n, a, b;
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	while(true) {
		int k = -1;
		for(int j = 1; j <= n; j++)
			if(!out[j] && (k == -1 || c[j].size() > c[k].size()))
				k = j;
		int o = 1;
		for(; c[k].count(o); o++);
		printf("%d %d\n", k, o);
		fflush(stdout);
		go(k, o);
		scanf("%d %d", &a, &b);		
		if(a == -1) return 0;
		go(a, b);
	}
}
