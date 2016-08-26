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
const int N = 50009;
int L[N], I[N], pai[N], ac[N], d[N], r1[N], l1[N], tempo, A[N];
vector<pii> adj[N];

void dfs(int u, int p, int c) {
	pai[u] = p;
	ac[u] = c;
	d[u] = ++tempo;
	I[u] = d[u];
	for(pii e : adj[u])
		if(e.fst != p) {
			dfs(e.fst, u, c + e.snd);
			if(r1[d[e.fst]] > r1[I[u]])
				I[u] = d[e.fst];
		}
}

void dfs2(int u, int p) {
	A[u] = A[pai[u]] | (1 << (r1[I[u]] - 1));
	if(!u || I[pai[u]] != I[u]) L[I[u]] = u;
	for(pii e : adj[u])
		if(e.fst != p)
			dfs2(e.fst, u);
}

inline int lca_bin(int a, int b) {
	if(r1[a] < r1[b]) swap(a, b);
	if((a >> r1[a]) == (b >> r1[a])) return a;
	int c = a ^ b;
	return ((a >> l1[c]) << l1[c]) | (1 << (l1[c] - 1));
}

int get(int a, int hz) {
	if(r1[I[a]] == hz) return a;
	int hw = l1[A[a] & (-1 << (hz - 1))];
	int Iw = (I[a] & (-1 << hw)) | (1 << (hw - 1));
	return pai[L[Iw]];
}

int lca(int a, int b) {
	if(r1[I[a]] < r1[I[b]]) swap(a, b);
	int l = r1[I[a]];
	int hz = r1[(A[a] & A[b]) >> (l - 1)] + (l - 1);
	a = get(a, hz); b = get(b, hz);
	if(d[a] < d[b]) return a;
	else return b;
}

int main() {
	int i, n, a, b, c;
	for(i = 1; i <= 50000; i++) {
		if(i & 1) r1[i] = 1;
		else r1[i] = 1 + r1[i>>1];
		l1[i] = 1 + l1[i>>1];
	}
	scanf("%d", &n);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	dfs(0, 0, 0);
	dfs2(0, 0);
	for_tests(t, tt) {
		scanf("%d %d", &a, &b);
		printf("%d\n", ac[a] + ac[b] - 2 * ac[lca(a, b)]);
	}
}
