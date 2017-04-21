#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
int seen[N]; vector<pii> adj[N];
ll d[N];

int main() {
	int i, a, b, c, n, k, x, m, s;
	for_tests(t, tt) {
		scanf("%d %d %d %d %d", &n, &k, &x, &m, &s);
		for(i = 1; i <= n; i++) adj[i].clear(), seen[i] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			adj[a].pb(pii(b, c));
			adj[b].pb(pii(a, c));
		}
		bool any = false;
		priority_queue<pli> pq;
		pq.push(pli(0, s));
		while(!pq.empty()) {
			pli p = pq.top(); pq.pop();
			if(seen[p.snd]) continue;
			seen[p.snd] = 1;
			d[p.snd] = -p.fst;
			for(pii e : adj[p.snd])
				pq.push(pli(p.fst - e.snd, e.fst));
			if(!any && p.snd <= k) {
				any = true;
				for(i = 1; i <= k; i++)
					pq.push(pli(p.fst - x, i));
			}
		}
		for(i = 1; i <= n; i++) printf("%lld%c", d[i], " \n"[i == n]);
	}
}
