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
const int N = 112345;
vector<int> adj[N];
int x[N], y[N]; ll kx[N], ky[N];

int main() {
	int i, n, m, f1, f2, a, b;
	scanf("%d %d %d %d", &n, &m, &f1, &f2);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);
	ll totx = accumulate(x, x + n, 0ll);
	ll toty = accumulate(y, y + n, 0ll);
	for(i = 0; i < n; i++) {
		kx[i] = totx - ll(n) * ll(x[i]);
		ky[i] = toty - ll(n) * ll(y[i]);
		ll tx = 0, ty = 0;
		for(int j : adj[i]) {
			kx[i] -= (x[j] - x[i]);
			ky[i] -= (y[j] - y[i]);
			tx += ll(x[j] - x[i]) * ll(f1);
			ty += ll(y[j] - y[i]) * ll(f1);
		}
		kx[i] = kx[i] * ll(f2) + tx;
		ky[i] = ky[i] * ll(f2) + ty;
		printf("%lld %lld\n", -kx[i], -ky[i]);
	}
	
}
