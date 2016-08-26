#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, long long> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
const int MAX = 100009;
int deg[MAX], ot[MAX], c[MAX];
ll val[2][MAX];
ll cor[2];
vector<pii> adj[MAX];
bool cmp(pii u) {
	return deg[u.fst] >= 300;
}

tuple<int, int, ll> es[MAX];

int main() {
	int t = 0, i, j, q, n, m, u, v, x, y; ll w; char op;
	while(scanf("%d %d", &n, &m) != EOF) {
		for(i = 0; i < n; i++) {
			scanf("%d", &c[i]);
			deg[i] = 0;
			val[0][i] = val[1][i] = 0;
		}
		ll tot = 0;
		cor[0] = cor[1] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %lld", &u, &v, &w);
			if(u > v) swap(u, v);
			get<0>(es[i]) = --u;
			get<1>(es[i]) = --v;
			get<2>(es[i]) = w;
			if(c[u] == c[v]) cor[c[u]] += w;
			tot += w;
		}
		sort(es, es + m);
		for(i = 0; i < m; i++) {
			int u = get<0>(es[i]), v = get<1>(es[i]); ll w = get<2>(es[i]);
			if(i < m - 1 && get<0>(es[i + 1]) == u && get<1>(es[i + 1]) == v) {
				get<2>(es[i + 1]) += w;
				continue;
			}
			deg[u]++; deg[v]++;
		}
		for(i = 0; i < m; i++) {
			int u = get<0>(es[i]), v = get<1>(es[i]); ll w = get<2>(es[i]);
			if(i < m - 1 && get<0>(es[i + 1]) == u && get<1>(es[i + 1]) == v) continue;
			if(make_pair(deg[u], u) >= make_pair(deg[v], v)) swap(u, v);
			adj[u].pb(pii(v, w));
			val[c[u]][v] += w;
		}
		scanf("%d", &q);
		printf("Case %d:\n", ++t);
		for(j = 0; j < q; j++) {
			scanf(" %c%*s %d", &op, &x);
			if(op == 'A') {
				scanf("%d", &y);
				if(x == y) printf("%lld\n", cor[x]);
				else printf("%lld\n", tot - cor[0] - cor[1]);
				continue;
			} --x;
			cor[c[x]] -= val[c[x]][x];
			cor[!c[x]] += val[!c[x]][x];
			for(i = 0; i < adj[x].size(); i++) {
				if(c[adj[x][i].fst] == c[x]) { cor[c[x]] -= adj[x][i].snd; }
				else { cor[!c[x]] += adj[x][i].snd; }
				val[c[x]][adj[x][i].fst] -= adj[x][i].snd;
				val[!c[x]][adj[x][i].fst] += adj[x][i].snd;
			}
			c[x] = !c[x];
		}
		for(i = 0; i < n; i++) adj[i].clear();
	}
	return 0;
}
