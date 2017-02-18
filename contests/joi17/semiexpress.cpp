#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
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

int n, m, k;
ll a, b, c, t;
ll s[112345];

int main() {
	int i;
	rd(n); rd(m); rd(k); k -= m;
	rd(a); rd(b); rd(c);
	rd(t);
	for(i = 0; i < m; i++) rd(s[i]);
	m--;
	ll tot = 0;
	priority_queue<tuple<ll, ll, ll>> pq;
	for(i = 0; i < m; i++) {
		ll cur = ll(s[i] - 1) * b;
		//printf("at [%lld] with %lld/%lld\n", s[i], cur, t);
		if(cur > t) break;
		tot += (cur <= t);
		//printf("++ %d\n", cur <= t);
		if(s[i + 1] - s[i] - 1 > (t - cur) / a) {
			tot += (t - cur) / a;
			ll w = (t - cur) / a + 1;
			//printf("+= %lld\n", (t - cur) / a);
			ll rem = min((t - cur -  w * c) / a + 1, s[i + 1] - s[i] - 1 - (t - cur) / a);
			if(t - cur - w * c >= 0 && rem > 0) {
				pq.push(make_tuple(rem, t - cur - w * c, s[i + 1] - s[i] - 1 - (t - cur) / a));
				//printf("%lld, %lld, %lld\n", rem, t - cur - w * c, s[i + 1] - s[i] - 1 - (t - cur) / a);
			}
		} else tot += s[i + 1] - s[i] - 1;
	}
	tot += (ll(b) * ll(n - 1) <= t);
	//printf("++ %d\n", (ll(b) * ll(n)) <= t);
	for(; k > 0 && !pq.empty(); k--) {
		ll rem, tim, left;
		tie(rem, tim, left) = pq.top(); pq.pop();
		//printf("++= %lld, %lld, %lld\n", rem, tim, left);
		tot += rem;
		if(rem != left && tim - ll(rem) * c >= 0)
			pq.push(make_tuple(min((tim - rem * c) / a + 1, left - rem), tim - rem * c, left - rem));
	}
	printf("%lld\n", tot - 1);
}
