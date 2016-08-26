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
vector<pii> adj[MAX];
int ok[MAX], acc[MAX];

int dfs(int u, int p, int sum) {
	acc[u] = sum;
	int tot = 0;
	for(pii e : adj[u]) {
		if(e.fst == p) continue;
		int x = dfs(e.fst, u, sum + e.snd);
		if(ok[e.fst]) tot += x + e.snd, ok[u] |= 2;
	}
	return tot;
}

int main() {
	int i, a, b, c, n, f;
	scanf("%d %d", &n, &f);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adj[--a].pb(pii(--b, c));
		adj[b].pb(pii(a, c));
	}
	for(i = 0; i < f; i++) {
		scanf("%d", &a);
		ok[--a] = 1;
	}
	a = dfs(0, -1, 0);
	int mx = 0;
	for(i = 0; i < n; i++)
		if(ok[i] & 1)
			mx = max(mx, acc[i]);
	printf("%d\n", a - mx);
}
