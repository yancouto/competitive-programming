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
const int N = 1009;
vector<int> adj[N];
int mx[N];
deque<int> f;
int seen[N], tempo;
void dfs(int u) {
	if(seen[u] == tempo) return;
	seen[u] = tempo;
	for(int v : adj[u])
		dfs(v);
	f.push_front(u);
}


int main() {
	int i, n, a, b, s, tt = 0;
	while(scanf("%d", &n) != EOF && n) {
		scanf("%d", &s); s--;
		for(i = 0; i < n; i++) adj[i].clear();
		while(scanf("%d %d", &a, &b) && a) {
			a--; b--;
			adj[a].pb(b);
		}
		f.clear();
		tempo++;
		for(i = 0; i < n; i++) dfs(i), mx[i] = 0;
		int m = -1, mi;
		for(i = 0; f[i] != s; i++);
		for(; i < n; i++) {
			if(mx[f[i]] > m || (mx[f[i]] == m && f[i] < mi)) m = mx[f[i]], mi = f[i];
			for(int v : adj[f[i]])
				mx[v] = max(mx[v], mx[f[i]] + 1);
		}
		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n", ++tt, s + 1, m, mi + 1);
	}
}
