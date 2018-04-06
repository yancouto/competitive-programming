#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

struct no {
	int u, d, p;
	bool operator < (no o) const { return d > o.d; }
};

const int N = 212345;
vector<int> adj[N];
vector<pii> adj_[N];
ll d[N];
int tempo = 1;
int low[N], sz[N];
map<pii, int> mrk;
int ans[N], seen[N];

void go(int u, int p) {
	d[u] = tempo++;
	low[u] = d[u];
	sz[u] = 1;
	seen[u] = 2;
	for(int v : adj[u]) {
		if(v == p) continue;
		else if(seen[v] == 2) {
			low[u] = min<int>(low[u], d[v]);
		} else {
			go(v, u);
			sz[u] += sz[v];
			low[u] = min<int>(low[u], low[v]);
			if(low[v] >= d[v]) {
				printf("(%d, %d) is a bridge\n", u, v);
				ans[mrk[pii(u, v)]] = sz[v];
			}
		}
	}
}


int main() {
	int i, n, m, a, b, c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		adj_[a].pb(pii(b, c));
		adj_[b].pb(pii(a, c));
		mrk[pii(a, b)] = mrk[pii(b, a)] = i;
	}
	priority_queue<no> pq;
	pq.push(no{0, 0, -1});
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(seen[x.u]) {
			if(x.d == d[x.u] && x.p != -1) {
				adj[x.p].pb(x.u);
				adj[x.u].pb(x.p);
			}
			continue;
		} else {
			if(x.p != -1) {
				adj[x.p].pb(x.u);
				adj[x.u].pb(x.p);
			}
			seen[x.u] = 1, d[x.u] = x.d;
		}
		for(pii e : adj_[x.u])
			pq.push(no{e.fst, x.d + e.snd, x.u});
	}
	go(0, 0);
	for(i = 0; i < m; i++)
		printf("%d\n", ans[i]);
}
