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
	ll i, n, m;
	scanf("%I64d %I64d", &n, &m);

	ll tot = 0;
	if(m > n) { tot = mod(mod(n) * mod(m - n)); m = n; }
	for(i = 1; i <= m && i * i <= n; i++)
		tot = mod(tot + (n % i));
	if(i > m) {
		printf("%d\n", int(tot));
		return 0;
	}
	ll mn = i;
	ll inv2 = 500000004;
	for(i = 1; i * i < n; i++) {
		ll s = mn, e = m;
		s = max(s, (n / (i + 1ll)) + 1ll);
		e = min(e, (n / i));
		if(s > e) continue;
		s = mod(s); e = mod(e);
		tot = mod(tot + mod((e - s + 1ll + modn) * (2ll * mod(n) - mod(i * (s + e)) + modn)) * inv2);
	}
	printf("%d\n", int(tot));
}
