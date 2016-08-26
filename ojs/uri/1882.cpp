// WA
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
const int MAX = 100009;
int seen[MAX], tempo, n, p[MAX];
ll dist[MAX];
vector<pii> adj[MAX];
void solve() {
	priority_queue<pii> pq;
	pq.push(pii(0, n - 1));
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(seen[x.snd] == tempo) continue;
		seen[x.snd] = tempo;
		dist[x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			if(seen[e.fst] != tempo)
				pq.push(pii(x.fst - e.snd, e.fst));
	}
}

int main() {
	int m, k, i, a, b, c;
	for_tests(t, tt) {
		scanf("%d %d %d", &n, &m, &k);
		for(i = 0; i < n; i++)
			adj[i].clear(), dist[i] = INT_MAX, p[i] = i;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			adj[a].pb(pii(b, c));
			adj[b].pb(pii(a, c));
		}
		tempo++;
		solve();
		sort(p, p + n, [](int i, int j) { return dist[i] > dist[j]; });
		typedef long double ld;
		ld mn = 1/0.;
		if(dist[0] != INT_MAX) mn = dist[0];
		for(i = n - 2; i >= 0 && dist[p[i]] != INT_MAX; i--)
			dist[p[i]] += dist[p[i + 1]];
		for(i++; i < n; i++)
			mn = min(mn, ld(n) / (n - i) * ld(k) + ld(dist[p[i]]) / (n - i));
		printf("%.3Lf\n", mn);
	}
}
