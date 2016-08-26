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

ll to(ll x) {
	return (x * (x + 1)) / 2ll;
}

ll ans(ll x) {
	if(x == 0) return 0;
	ll tot = 0;
	for(ll i = 1; i <= x; i <<= 1) {
		tot += to(x / i);
		tot -= (to(x / (i << 1)) << 1);
	}
	return tot;
}

int main() {
	int a, b;
	for_tests(t, tt) {
		scanf("%d %d", &a, &b);
		printf("%lld\n", ans(b) - ans(a - 1));
	}
}
