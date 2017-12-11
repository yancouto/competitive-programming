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

const int N = 312345;
vector<int> adj[N];
ll val[N];

void go(int u, int p, int d, ll a, ll b) {
	if(d < 0) return;
	val[u] = mod(val[u] + a);
	for(int v : adj[u])
		if(v != p)
			go(v, u, d - 1, b, mod(a + b));
}

int main() {
	int i, n, q, a, b, op;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &q);
		for(i = 0; i <= n; i++) adj[i].clear(), val[i] = 0;
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b);
			adj[a].pb(b);
			adj[b].pb(a);
		}
		for(i = 0; i < q; i++) {
			scanf("%d %d", &op, &a);
			if(op == 1) {
				int A, B, d;
				scanf("%d %d %d", &d, &A, &B);
				go(a, a, d, A, B);
			} else
				printf("%lld\n", val[a]);
		}
	}
}
