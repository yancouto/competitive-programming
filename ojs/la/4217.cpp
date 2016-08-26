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
const int MAX = 10009;
int S[MAX], sz[MAX];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
void join(int a, int b) {
	a = find(a); b = find(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int deg[MAX], d[MAX], low[MAX], tempo;
vector<pii> adj1[MAX], adj2[MAX];
int dfs(int u, int pai) {
	if(d[u]) return 0;
	low[u] = d[u] = ++tempo;
	int s = 1;
	for(pii p : adj1[u]) {
		if(p.fst == pai) continue;
		int a = dfs(p.fst, u);	
		low[u] = min(low[u], low[p.fst]);
		if(low[p.fst] > d[u]) {
			ll price = ll(a) * ll(sz[find(u)] - a) * ll(p.snd);
			adj2[u].pb(pii(p.fst, price));
			adj2[p.fst].pb(pii(u, price));
			deg[u]++; deg[p.fst]++;
		}
		s += a;
	}
	return s;
}
int c[MAX], d2[MAX], ig[MAX], n, m; ll cur[MAX];
bool pos(ll mx) {
	queue<int> q;
	for(int i = 0; i < n; i++) {
		cur[i] = c[i];
		d2[i] = deg[i]; ig[i] = 0;
		if(d2[i] == 1) q.push(i);
	}
	while(!q.empty()) {
		int x = q.front(); q.pop();
		if(ig[x]) continue;
		for(pii p : adj2[x]) {
			if(ig[p.fst]) continue;
			if(cur[x] + p.snd <= mx) cur[x] += p.snd;
			else cur[p.fst] += p.snd;
			if(cur[p.fst] > mx) return false;
			ig[x] = true; d2[p.fst]--;
			if(d2[p.fst] == 0) ig[p.fst] = true;
			else if(d2[p.fst] == 1) q.push(p.fst);
			break;
		}
	}
	return true;
}

int main() {
	int i, u, v, w;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		ll l = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &c[i]);
			l = max<ll>(l, c[i]);
			S[i] = i; sz[i] = 1;
			adj1[i].clear(); adj2[i].clear();
			deg[i] = d[i] = 0; tempo = 0;
		}
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &w);
			join(--u, --v);
			adj1[u].pb(pii(v, w));
			adj1[v].pb(pii(u, w));
		}
		for(i = 0; i < n; i++)
			dfs(i, -1);
		ll r = 1000000000000000000;
		while(l < r) {
			ll mid = (l + r) / 2;
			if(pos(mid)) r = mid;
			else l = mid + 1;
		}
		printf("Case %d: %lld\n", tt, l);
	}
	return 0;
}
