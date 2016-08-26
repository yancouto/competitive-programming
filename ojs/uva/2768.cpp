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
const int MAX = 1009;
int dist[MAX], bad[MAX];
vector<pii> adj[MAX];
int pai[MAX];

int main() {
	int i, n, m, a, b, t, k;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &t);
			adj[b].pb(pii(a, t));
		}
		memset(dist, 0, sizeof dist);
		memset(bad, 0, sizeof bad);
		for(k = 0; k < n; k++)
			for(i = 0; i < n; i++)
				for(pii e : adj[i])
					if(dist[e.fst] > dist[i] + e.snd) {
						dist[e.fst] = dist[i] + e.snd;
					}
		bool any = false;
		for(k = 0; k < n + 2; k++)
			for(i = 0; i < n; i++)
				for(pii e : adj[i])
					if(dist[e.fst] > dist[i] + e.snd) {
						bad[e.fst] = any = true;
						dist[e.fst] = -10000000;
					}
		if(!any) { printf("Case %d: impossible\n", tt); continue; }
		printf("Case %d:", tt);
		for(i = 0; i < n; i++)
			if(bad[i])
				printf(" %d", i);
		putchar('\n');
	}
}
