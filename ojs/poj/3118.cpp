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

ll memo[1123][112][2];
ll cyc(int k, int n, bool pr) {
	if(n == 1) return mod(k - 1 - !pr);
	ll &r = memo[k][n][pr];
	if(r != -1) return r;
	return r = mod(cyc(k, n - 1, false) * ll(k - 1 - !pr) + cyc(k, n - 1, true) * ll(!pr));
}

int c[112], seen[112], tempo;
int h[112];

vector<int> adj[112];

int bad;
int go(int u, int h) {
	seen[u] = tempo;
	::h[u] = h;
	if(seen[c[u]] == tempo) {
		seen[u] = tempo + 1;
		return h - ::h[c[u]] + 1;
	}
	int x = 0;
	if(seen[c[u]] != tempo + 1)
		x = go(c[u], h + 1);
	seen[u] = tempo + 1;
	return x;
}

int main() {
	int i, t, n;
	memset(memo, -1, sizeof memo);
	scanf("%d", &t);
	while(t--) {
		ll k;
		scanf("%d %lld", &n, &k);
		for(i = 0; i < n; i++) adj[i].clear();
		for(i = 0; i < n; i++) {
			scanf("%d", &c[i]);
		}
		tempo += 2;
		ll ans = 1;
		int tot = n;
		for(i = 0; i < n; i++)
			if(seen[i] != tempo) {
				int szc = go(i, 0);
				if(szc == 0) continue;
				//printf("szc %d\n", szc);
				tot -= szc;
				ans = mod(ans * mod(cyc(k, szc - 1, true) * k));
			}
		while(tot--) ans = mod(ans * (k - 1ll));
		printf("%lld\n", ans);
	}
}
