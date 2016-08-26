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

ll mdc(ll a, ll b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int main() {
	ll a, b, c, d;
	for_tests(t, tt) {
		scanf("%lld %lld %lld %lld", &a, &b, &c, &d);
		ll y = abs(a - b);
		ll x = mdc(c, d);
		printf("%lld\n", min(y % x, x - (y % x)));
	}
}
