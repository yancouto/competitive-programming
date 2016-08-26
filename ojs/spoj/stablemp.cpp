#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n;
vector<int> adj[1003];
int M[1003];

bool unstable(int u, int v) {
	if(M[v] == -1) return true;
	int posu = search_n(adj[v].begin(), adj[v].end(), 1, u) - adj[v].begin();
	if(posu < M[v]) return true;
	return false;
}

int main() {
	int i, j, x;
	for_tests(t, tt) {
		scanf("%d", &n);
		vector<int> S;
		for(i = 0; i < n; i++) {
			scanf("%*d"); adj[i].clear();
			S.pb(i);
			M[i] = -1;
			for(j = 0; j < n; j++) {
				scanf("%d", &x);
				adj[i].pb(n + (--x));
			}
		}
		for(i = n; i < 2*n; i++) {
			scanf("%*d"); adj[i].clear();
			M[i] = -1;
			for(j = 0; j < n; j++) {
				scanf("%d", &x);
				adj[i].pb(--x);
			}
		}
		while(!S.empty()) {
			int u = S.back(); S.pop_back();
			for(i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i];
				if(!unstable(u, v)) continue;
				if(M[v] != -1) {
					S.pb(adj[v][M[v]]);
					M[adj[v][M[v]]] = -1;
					M[v] = -1;
				}
				M[u] = i; M[v] = search_n(adj[v].begin(), adj[v].end(), 1, u) - adj[v].begin();
				break;
			}
		}
		for(i = n; i < 2*n; i++)
			printf("%d %d\n", i - n+1, adj[i][M[i]]+1);
	}
	return 0;
}
