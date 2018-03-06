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

int val(int x) {
	int v = 0;
	while(x != 0) {
		int k = (x % 10);
		if(k & 1) v += k;
		else v -= k;
		x /= 10;
	}
	return abs(v);
}

const int N = 2000009;

ll v[N], acc[N], rv[N], racc[N];

int main() {
	int i, n;
	for(i = 2; i < N; i++) {
		v[i] = val(i);
		acc[i] = acc[i - 1] + ll(v[i]) * ll(i - 1ll);
	}
	rv[N - 1] = v[N - 1];
	racc[N - 1] = v[N - 1];
	for(i = N - 2; i > 1; i--)
		rv[i] = rv[i + 1] + ll(v[i]) * ll(N - i),
		racc[i] = racc[i + 1] + ll(v[i]);
	
	for_tests(tn, tt) {
		scanf("%d", &n);
		ll ans = acc[n + 1] + (rv[n + 2] - rv[2 * n + 1]) - (racc[n + 2] - racc[2 * n + 1]) * ll(N - 2 * n - 1);
		ll ans2 = 0;
		//for(ll i = 2; i <= 2 * n; i++) {
		//	if(i <= n + 1) ans2 += val(i) * (i - 1ll);
		//	else ans2 += val(i) * ll(2 * n + 1 - i);
		//}
		//for(i = 1; i <= n; i++)
		//	for(int j = 1; j <= n; j++) {
		//		assert(val(i + j) == val2(i + j));
		//		ans2 += val(i + j);
		//	}
		//assert(ans == ans2);
		printf("%lld\n", ans);
	}
}
