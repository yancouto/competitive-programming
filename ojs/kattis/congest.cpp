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
const int N = 120009;

vector<pii> adj[N];
int to[N], he[N], fl[N], nx[N], dist[N], en, cp[N];

int seen[N], tempo = 2;
void solve() {
	priority_queue<pii> pq;
	pq.push(pii(0, 0));
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(seen[x.snd]) continue;
		seen[x.snd] = 1;
		dist[x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			pq.push(pii(x.fst - e.snd, e.fst));
	}
}

void add_edge(int u, int v) {
	to[en] = u; nx[en] = he[v]; he[v] = en++;
	cp[en] = 1;	to[en] = v; nx[en] = he[u]; he[u] = en++;
}

bool dfs(int u, int t) {
	if(u == t) return true;
	if(seen[u] == tempo) return false;
	seen[u] = tempo;
	for(int e = he[u]; e != -1; e = nx[e])
		if(cp[e] - fl[e] && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

int max_flow(int s, int t) {
	tempo++;
	int fl = 0;
	while(dfs(s, t)) fl++, tempo++;
	return fl;
}

int ca[N];
int main() {
	int i, n, m, c, a, b, C, j;
	memset(he, -1, sizeof he);
	scanf("%d %d %d", &n, &m, &c);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &C); a--; b--;
		adj[a].pb(pii(b, C));
		adj[b].pb(pii(a, C));
	}
	solve();
	for(i = 0; i < n; i++)
		for(pii e : adj[i])
			if(dist[e.fst] == dist[i] - e.snd)
				add_edge(i, e.fst);
	for(i = 0; i < c; i++)
		scanf("%d", &ca[i]), ca[i]--;
	sort(ca, ca + c, [](int i, int j) { return dist[i] < dist[j]; });
	int tot = 0;
	for(i = 0; i < c; ) {
		int pr = en;
		for(j = i; j < c && dist[ca[i]] == dist[ca[j]]; j++)
			add_edge(N - 1, ca[j]);
		tot += max_flow(N - 1, 0);
		he[N - 1] = -1;		
		i = j;
		for(j = pr; j < en; j++) cp[j] = 0;
		for(j = 0; j < en; j++) fl[j] = 0;
	}
	printf("%d\n", tot);
}
