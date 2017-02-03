#include <bits/stdc++.h>
using namespace std;
#define t first
#define d second
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

int n;

int main() {
#ifdef ONLINE_JUDGE
	freopen("pulp.in", "r", stdin);
	freopen("pulp.out", "w", stdout);
#endif
	int i, j;
	rd(n);
	multiset<pii> evs;
	for(i = 0; i < n; i++) {
		ll r, p;
		rd(r); rd(p);
		evs.insert(pii(r, p));
	}
	evs.insert(pii(LLONG_MAX, -1));
	multiset<ll> cur; ll tot = 0;
	while(true) {
		pii x = *evs.begin(); evs.erase(evs.begin());
		if(x.t == LLONG_MAX) { printf("%lld\n", tot); return 0; }
		if(x.d == -1) tot += x.t;
		else cur.insert(x.d);
		if(cur.empty()) continue;
		ll sm = *cur.begin(); cur.erase(cur.begin());
		if(evs.begin()->t - x.t >= sm) evs.insert(pii(x.t + sm, -1));
		else cur.insert(sm - (evs.begin()->t - x.t));
	}
}
