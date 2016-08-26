// BLA
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
vector<int> adj[N];
int dv[20009], a[N], seen[N], d[N], tempo, low[N], ok[N];
int root, pai[N]; bool bad;
void dfs(int u, int p) {
	if(seen[u]) return;
	seen[u] = true;
	pai[u] = p;
	d[u] = low[u] = tempo++;
	bool cut = false;
	vector<int> sons;
	for(int v : adj[u])
		if(!seen[v]) {
			sons.pb(v);
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > d[u] && !ok[v]) bad = true;
			if(low[v] >= d[u] && (u != root || sons.size() > 1)) cut = true;
			if(ok[v] && low[v] <= d[u]) ok[u] = true;
		} else if(v != p && d[v] < d[u]) {
			low[u] = min(low[u], d[v]);
			ok[v] = ok[u] = true;
		}
	if(!cut && u != root) return;
	int nok = 0;
	int nbridge = 0;
	for(int v : sons)
		if(low[v] == d[u]) { //!bridge
			nok += !ok[v];
			nbridge++;
		}
	if(nok > 1) bad = true;
	if(nbridge == 0 && ok[u] == false) bad = true;
	if(nok || (
}


int main() {
	int i, j, n;
	for(i = 2; i <= 20000; i++)
		if(!dv[i])
			for(j = i * i; j <= 20000; j += i)
				dv[j] = 1;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	if(n <= 2) { puts("Impossible"); return 0; }
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if(!dv[a[i] + a[j]])
				adj[i].pb(j),
				adj[j].pb(i);
	bad = false;
	for(i = 0; i < n; i++)
		if(!seen[i]) {
			root = i;
			dfs(i, -1);
		}
	if(bad) { puts("Impossible"); return; }
	printf("ok %d\n", !bad);
}
