#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int a[112345];

ll mdc(ll a, ll b) { return b? mdc(b, a % b) : a; }

int main() {
	int i, n, s, t;
	scanf("%d %d %d", &n, &s, &t);
	multiset<int> so;
	for(i = 0; i < n; i++) scanf("%d", &a[i]), so.insert(a[i]);
	sort(a, a + n);
	ll mn = LLONG_MAX, mx = LLONG_MIN, sum = 0;
	for(i = 0; i < n; i++) {
		if(i && a[i] == a[i - 1]) continue;
		ll dt;
		if(i == 0) dt = a[0] + (s - a[n - 1]);
		else dt = a[i] - a[i - 1];
		multiset<int> S = so;
		int pos = a[i];
		ll tot = 0;
		while(!S.empty()) {
			auto it = S.lower_bound(pos);
			if(it == S.end()) it = S.begin();
			int nx = *it;
			if(nx >= pos) tot += nx - pos;
			else tot += (s - pos) + nx;
			S.erase(it);
			tot += t;
			pos = (nx + t) % s;
		}
		mn = min(mn, tot);
		mx = max(mx, tot + dt - 1ll);
		sum += ((tot + tot + dt - 1ll) * dt) / 2ll;
	}
	ll m = mdc(sum, s);
	printf("%lld\n%lld\n%lld/%lld\n", mn, mx, sum / m, s / m);
}
