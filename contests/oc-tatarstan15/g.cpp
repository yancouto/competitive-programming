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

ll c = 1000000ll;
ll t[100009];

int main() {
	int i, n;
	ll h, m, s;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &h, &m, &s);
		t[i] = h * c * c + m * c + s;
	}
	sort(t, t + n);
	for(i = 1; i < n; i++)
		t[i] += t[i - 1];
	ll mn = LLONG_MAX;
	for(i = 0; i < n; i++) {
		ll tot = 0;
		ll a = t[i];
		if(i) a -= t[i - 1];
		tot = a * ll(i + 1) - t[i];
		tot += ll(n - 1 - i) * (a + 12ll * c * c) - (t[n - 1] - t[i]);
		mn = min(mn, tot);
	}
	ll tot = mn;
	printf("%lld %lld %lld\n", tot / (c * c), (tot / c) % c, tot % c);
}
