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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
const int N = 212345;
ll t[N];
set<pii> evs;

ll go(ll tm) {
	ll tot = 0;
	for(pii p : evs) {
		if(tm < p.fst) continue;
		tot += 1 + (tm - p.fst) / t[p.snd];
	}
	return tot;
}

ll solve(ll k) {
	k--;
	evs.clear();
	evs.insert(pii(t[0], 0));
	int lst = 1; ll cur = 0;
	for(; lst < n; lst++) {
		pii x = *evs.begin(); evs.erase(x);
		if(--k == 0) return x.fst;
		cur = x.fst;
		evs.insert(pii(cur + t[x.snd], x.snd));
		evs.insert(pii(cur + t[lst], lst));
	}
	ll l = cur, r = 1e18;
	while(l < r) {
		ll m = (l + r) / 2;
		if(go(m) >= k) r = m;
		else l = m + 1;
	}
	return l;
}


int main() {
	int i, j, m, x;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%lld", &t[i]);
	sort(t, t + n);
	for(i = 0; i < m; i++) {
		scanf("%d", &x);
		printf("%lld\n", solve(x + 1));
	}
}
