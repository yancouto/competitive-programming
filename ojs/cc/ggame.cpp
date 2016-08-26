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

ll xor_to_n(ll n) {
	ll resp = 0;
	for(ll i = (1ll << 62); i > 2; i >>= 1) {
		if(!(n & i)) continue;
		ll g = n - i + 1;
		if(g & 1) resp |= i;
		n ^= i;
	}
	if(n == 1) resp |= 1;
	if(n == 2) resp |= 3;
	return resp;
}

int main() {
	ll x, m;
	for_tests(t, tt) {
		scanf("%lld %lld", &x, &m);
		if(m == 0) { puts("BOB"); continue; }
		if((x & 1) && (m & 1)) { puts("ALICE"); continue; }
		x >>= 1;
		ll val = xor_to_n(x + m - 1);
		if(x) val ^= xor_to_n(x - 1);
		if(val) puts("ALICE");
		else puts("BOB");
	}
}
