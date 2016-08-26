#include <bits/stdc++.h>
using namespace std;
#define x first
#define i second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 112345;
int xs[N], xf[N];

int main() {
	int i, n;
	scanf("%d", &n);
	ll bef = 0, aft = 0;
	ll bi = 0, ai = 0;
	vector<pii> evs;
	for(i = 1; i <= n; i++) {
		scanf("%d %d", &xs[i], &xf[i]);
		if(xs[i] > xf[i]) swap(xs[i], xf[i]);
		evs.pb(pii(xs[i], i));
		evs.pb(pii(xf[i], -i));
		aft += xs[i]; ai++;
	}
	sort(evs.begin(), evs.end());
	ll mn = LLONG_MAX;
	for(pii ev : evs) {
		if(ev.i > 0) {
			aft -= xs[ev.i]; ai--;
			mn = min(mn, ll(ev.x) * bi - bef + aft - ai * ll(ev.x));
		}
		else {
			mn = min(mn, ll(ev.x) * bi - bef + aft - ai * ll(ev.x));
			bi++; bef += xf[-ev.i];
		}
	}
	printf("%lld\n", mn);
}
