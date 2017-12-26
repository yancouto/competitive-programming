#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;
int m[100];

int phi(int x) {
	int y = x;
	for(int i = 2; i * i <= x; i++) {
		if(!(x % i)) {
			y = (y / i) * (i - 1);
			while(!(x % i)) x /= i;
		}
	}
	if(x > 1) y = (y / x) * (x - 1);
	return y;
}

ll fexp(ll x, ll p, ll m) {
	ll r = 1 % m;
	for(; p; p >>= 1, x = (x * x) % m)
		if(p & 1)
			r = (r * x) % m;
	return r;
}

ll w[212345];

int main() {
	int i, j;
	rd(n); rd(m[0]);
	for(i = 0; i < n; i++) rd(w[i]);
	for(i = 0; m[i] != 1; i++) m[i + 1] = phi(m[i]);
	int mx = i;
	int q, l, r;
	rd(q);
	while(q--) {
		rd(l); rd(r); l--; r--;
		r = min(r, l + mx - 1);
		ll ans = w[r] % m[r - l];
		for(i = r - 1; i >= l; i--)
			ans = fexp(w[i], ans, m[i - l]);
		printf("%lld\n", ans);
	}
}
