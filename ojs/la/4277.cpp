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
int n, m;
vector<pii> adj[2003];
int dist[2003], p[2003];
int pe[2003];

int main() {
	int i, j, k, a, b, c;
	while(scanf("%d %d", &n, &m) != EOF) {
		for(i = 0; i < 2*n; i++) {
			adj[i].clear();
			dist[i] = 100000000;
			pe[i] = -1;
			p[i] = -1;
			if(!(i % 2)) adj[i].pb(pii(i + 1, 0));
		}
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			adj[2*(--a)+1].pb(pii(2*(--b), c));
		}
		dist[1] = 0;
		for(i = 0; i < 2*n - 1; i++)
			for(j = 0; j < 2*n; j++)
				for(k = 0; k < adj[j].size(); k++) {
					pii e = adj[j][k];
					if(dist[e.fst] > dist[j] + e.snd) {
						dist[e.fst] = dist[j] + e.snd;
						pe[e.fst] = k;
						p[e.fst] = j;
					}
				}
		i = 2*n - 2;
		int tot = dist[2*n - 2];
		while(i != 1) {
			pii p2 = adj[p[i]][pe[i]];
			swap(adj[p[i]][pe[i]], adj[p[i]].back());
			adj[p[i]].pop_back();
			adj[i].pb(pii(p[i], -p2.snd));
			i = p[i];
		}
		for(i = 0; i < 2*n; i++) {
			dist[i] = 100000000;
		}
		dist[1] = 0;
		for(i = 0; i < 2*n - 1; i++)
			for(j = 0; j < 2*n; j++)
				for(pii e : adj[j])
					if(dist[e.fst] > dist[j] + e.snd) {
						dist[e.fst] = dist[j] + e.snd;
					}
		printf("%d\n", tot + dist[2*n - 2]);		
	}
	return 0;
}
