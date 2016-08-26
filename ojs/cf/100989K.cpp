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
const int N = 312345;

vector<int> adj[N];
int d[N], f[N], ex[N], tempo, sz[N], p[N];

int dfs(int u) {
	d[u] = tempo++;
	for(int v : adj[u])
		sz[u] += 1 + dfs(v);
	f[u] = tempo;
	return sz[u];
}

int bit[N];
int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}
inline int get(int i, int j) { return get(j) - get(i - 1); }

void add(int i, int x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

int main() {
	int i, j, n, x, q;
	scanf("%d %d", &n, &q);
	for(i = 1; i <= n; i++) {
		scanf("%d", &p[i]);
		adj[p[i]].pb(i);
	}
	for(i = 0; i <= n; i++) ex[i] = true;
	dfs(0);
	int cur = sz[0] + 1;
	for(i = 0; i < q; i++) {
		scanf("%d", &x);
		if(ex[x]) {
			int pv = get(d[x], f[x] - 1);
			cur -= sz[x] - pv;
			add(d[x], sz[x] - pv);
		} else {
			int pv = get(d[x], d[x]);
			cur += pv;
			add(d[x], -pv);
		}
		ex[x] = !ex[x];
		printf("%d ", cur);
	}
	putchar('\n');
}
