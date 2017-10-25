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

const int N = 21234;
vector<pii> adj[N];
int has[N][2];

int main() {
	int i, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	priority_queue<pii> pq;
	pq.push(pii(0, 0));
	while(!pq.empty()) {
		int x = pq.top().snd / 2;
		int p = pq.top().snd % 2;
		ll d = -pq.top().fst;
		pq.pop();
		if(has[x][p]) continue;
		has[x][p] = 1;
		if(x == n - 1) { printf("%lld\n", d); return 0; }
		for(pii e : adj[x]) {
			ll nd = d + 1;
			if(e.snd > d) {
				if((e.snd & 1) == p)
					nd = e.snd + 1;
				else nd = e.snd + 2;
			}
			pq.push(pii(-nd, 2 * e.fst + (!p)));
		}
	}
	puts("-1");
}
