#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
const int N = 112345;

int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int a[N], b[N], c[N], r[N];
vector<pii> adj[N];

int seen[N], n, m, t;
void dfs(int u, int flip, int want) {
	r[u] = flip;
	seen[u] = t;
	for(pii a : adj[u]) {
		int v = a.fst, e = a.snd;
		if(seen[v] == t) continue;
		dfs(v, (c[e] ^ flip) != want, want);
	}
}

bool ok(int u, int want) {
	if(seen[u] == t) return true;
	seen[u] = t;
	for(pii a : adj[u]) {
		int v = a.fst, e = a.snd;
		if((c[e] ^ r[::a[e]] ^ r[b[e]]) != want) return false;
		if(!ok(v, want)) return false;
	}
	return true;
}

bool go(int u, int flip, int want) {
	t++;
	dfs(u, flip, want);
	t++;
	return ok(u, want);
}

int main() {
	int i, j; char c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < m; i++) {
		scanf("%d %d %c", &a[i], &b[i], &c); a[i]--; b[i]--; ::c[i] = c == 'R';
		join(a[i], b[i]);
		adj[a[i]].pb(pii(b[i], i));
		adj[b[i]].pb(pii(a[i], i));
	}
	for(j = 0; j < 2; j++) {
		for(i = 0; i < n; i++)
			if(i == find(i)) {
				if(go(i, 0, j) || go(i, 1, j)) continue;
			}
		if(i == n) break;
	}
	if(j == 2) puts("-1");
	// fazer menor
}
