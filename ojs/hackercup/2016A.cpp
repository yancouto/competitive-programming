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

int x[2009], y[2009];
inline ll qd(ll x) { return x * x; }
inline ll dist(int i, int j) {
	return qd(x[i] - x[j]) + qd(y[i] - y[j]);
}

ll a[2009];

int main() {
	int i, j, k, g, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		ll tot = 0;
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++)
				a[j] = dist(i, j);
			sort(a, a + n);
			for(k = 0; k < n; ) {
				for(g = k; g < n && a[g] == a[k]; g++);
				tot += (ll(g - k) * ll(g - k - 1)) / 2ll;
				k = g;
			}
		}
		printf("Case #%d: %lld\n", tt, tot);
	}
}
