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
ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll fexp(ll n, ll p) {
	ll r = 1;
	for(; p; p >>= 1, n = mod(n * n))
		if(p & 1)
			r = mod(r * n);
	return r;
}

int main() {
	ll b, e;
	for_tests(t, tt) {
		scanf("%lld %lld %lld", &b, &e, &modn);
		printf("%d. %lld\n", tt, fexp(mod(b), e));
	}
}
