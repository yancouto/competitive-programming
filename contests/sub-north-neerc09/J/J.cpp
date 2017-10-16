#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

inline bool blow(ll x, ll y) {
	return x && y >= LLONG_MAX / x;
}

inline ll solve(ll a, ll p) {
	return a / p;
}

inline ll solve(ll a, ll b, ll p) {
	return solve(b, p) - solve(a - 1, p);
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("jealous.in", "r", stdin);
	freopen("jealous.out", "w", stdout);
#endif
	ll a, b, p, q, i, j;
	scanf("%lld %lld %lld %lld", &a, &b, &p, &q);
	ll xx = 1;
	ll tot = 0;
	for(i = 0; i <= 61; i++) {
		ll x = xx;
		for(j = 0; j < i; j++) {
			ll ct = solve(a, b, x);
			if(!blow(x, p)) ct -= solve(a, b, x * p);
			if(!blow(x, q)) {
				ct -= solve(a, b, x * q);
				if(!blow(x * q, p)) ct += solve(a, b, x * p * q);
			}
			tot += ct;
			if(blow(x, q)) break;
			x *= q;
		}
		if(blow(xx, p)) break;
		xx *= p;
	}
	printf("%lld\n", tot);
}

