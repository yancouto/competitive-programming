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

int main() {
	ll n1, n2, m;
	for_tests(t, tt) {
		scanf("%lld %lld %lld", &n1, &n2, &m);
		ll tot = max(n1, n2) - min(n1, n2);
		n1 = min(n1, n2);
		tot += 2ll * max(0ll, n1 - (m * (m + 1)) / 2ll);
		printf("%lld\n", tot);
	}
}
