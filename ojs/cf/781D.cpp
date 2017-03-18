#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
const int N = 512, L = 61;

bitset<500> adj[2][N];

bool seen[N][L][2];
bitset<500> memo[N][L][2];
bitset<500> &solve(int a, int i, bool f) {
	if(i == 0) return adj[f][a];
	bitset<500> &r = memo[a][i][f];
	if(seen[a][i][f]) return r;
	seen[a][i][f] = true;
	bitset<500> &b1 = solve(a, i - 1, f);
	for(int b = 0; b < n; b++)
		if(b1[b])
			r |= solve(b, i - 1, !f);

	return r;
}

ll memo2[N][L][2];
ll mx(int a, int i, bool f) {
	if(i == 0) return adj[f][a].any();
	ll &r = memo2[a][i][f];
	if(r != -1) return r;
	if(!solve(a, i, f).any()) return r = mx(a, i - 1, f);
	bitset<500> &ad = solve(a, i, f);
	for(int b = 0; b < n; b++)
		if(ad[b])
			r = max(r, (1ll << i) + mx(b, i - 1, !f));
	return r;
}

int main() {
	memset(memo2, -1, sizeof memo2);
	int i, m, a, b, t;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &t); a--; b--;
		adj[t][a][b] = 1;
	}
	for(i = 0; i < n; i++)
		if(solve(i, 60, false).any()) {
			puts("-1");
			return 0;
		}
	ll ans = 0;
	for(i = 0; i < n; i++)
		ans = max(ans, mx(i, 59, 0));
	if(ans > 1000000000000000000ll) puts("-1");
	else printf("%lld\n", ans);
}
