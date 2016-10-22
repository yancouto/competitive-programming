#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 112345;
int n, tempo, seen[N];
vector<pii> adj[N];
ll d[3][N];
void dij(int i, int s) {
	tempo++;
	priority_queue<pii> pq;
	pq.push(pii(0, s));
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(seen[x.snd] == tempo) continue;
		seen[x.snd] = tempo;
		d[i][x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			if(seen[e.fst] < tempo)
				pq.push(pii(x.fst - e.snd, e.fst));
	}
}

int main() {
	int i, n, m, s, t, v, a, b, c;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &m);
		scanf("%d %d %d", &s, &t, &v); s--; t--; v--;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c); a--; b--;
			adj[a].pb(pii(b, c));
			adj[b].pb(pii(a, c));
		}
		dij(0, s);
		dij(1, t);
		dij(2, v);
		ll mn = LLONG_MAX;
		for(i = 0; i < n; i++) mn = min(mn, d[0][i] + d[1][i] + d[2][i]);
		printf("%lld\n", mn);
		for(i = 0; i < n; i++) adj[i].clear();
	}
}
