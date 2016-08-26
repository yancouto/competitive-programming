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

ll form(ll n) {
	n -= 3ll;
	ll k = n / 3ll;
	ll odd = (n & 1)? k/2ll + 1ll: (k+1ll) / 2ll;
	return ((k + 1ll) * (2ll * n - 3ll * k + 4ll)) / 4ll - (odd / 2ll);
}

// <= k
ll solve(ll k) {
	if(k == 0) return 2;
	ll L = 3ll, R = 2000000000ll;
	while(L < R) {
		ll m = (L + R + 1ll) / 2ll;
		ll x = form(m);
		if(x <= k) L = m;
		else R = m - 1ll;
	}
	return L;
}


//ll memo[1000][1000][10];
//ll solve(int x, int mx, int p) {
//	if(p == 3) return x == 0;
//	ll &r = memo[x][mx][p];
//	if(r != -1) return r;
//	r = 0;
//	for(int i = 1; i <= mx && i <= x; i++)
//		r += solve(x - i, i, p + 1);
//	return r;
//}

int main() {
	//memset(memo, -1, sizeof memo);
	ll l, r;
	//for(ll i = 1; i <= 900; i++) assert(form(i) == solve(i, i, 0));
	//while(true) {
	//	scanf("%lld", &l);
	//	printf("f(%lld) = %lld\n", l, form(l));
	//	//printf("should %lld\n", solve(l, l, 0));
	//}
	scanf("%lld %lld", &l, &r);
	//printf("solve(%lld) = %lld\nsolve(%lld) = %lld\n", r, solve(r), l - 1, solve(l - 1));
	printf("%lld\n", solve(r) - solve(l - 1));
}
