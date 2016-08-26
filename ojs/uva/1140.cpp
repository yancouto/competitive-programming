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
const int N = 209;

char s[N][100], s1[100], s2[100];
map<string, int> mp;
vector<string> v;
vector<int> adj[N];
int d[N], low[N], seen[N], tempo;

void dfs(int u, int p) {
	int nf = 0; bool any = false;
	seen[u] = true;
	d[u] = low[u] = tempo++;
	for(int v : adj[u])
		if(!seen[v]) {
			dfs(v, u); nf++;
			low[u] = min(low[u], low[v]);
			if(low[v] >= d[u]) any = true;
		} else if(v != p) low[u] = min(low[u], d[v]);
	if(u == p? nf > 1 : any) v.pb(s[u]);
}

int main() {
	int i, n, tt = 0;
	while(scanf("%d", &n) && n) {
		if(tt) putchar('\n');
		mp.clear(); v.clear();
		for(i = 0; i < n; i++) {
			adj[i].clear(); seen[i] = false;
			scanf("%s", s[i]);
			mp[s[i]] = i;
		}
		for_tests(m, mm) {
			scanf("%s %s", s1, s2);
			adj[mp[s1]].pb(mp[s2]);
			adj[mp[s2]].pb(mp[s1]);
		}
		for(i = 0; i < n; i++)
			if(!seen[i])
				dfs(i, i);
		sort(v.begin(), v.end());
		printf("City map #%d: %d camera(s) found\n", ++tt, (int)v.size());
		for(string s : v)
			printf("%s\n", s.c_str());
	}
}
