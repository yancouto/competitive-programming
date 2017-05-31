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

const int N = 112345;
int h[N], l[N], r[N];

int main() {
	int i, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &h[i]);
		r[0] = 1;
		for(i = 1; i < n; i++)
			r[i] = min(r[i - 1] + 1, h[i]);
		l[n - 1] = 1;
		for(i = n - 2; i >= 0; i--)
			l[i] = min(l[i + 1] + 1, h[i]);
		ll mx = 0;
		for(i = 0; i < n; i++)
			mx = max<ll>(mx, min(l[i], r[i]));
		printf("%lld\n", accumulate(h, h + n, 0ll) - mx * mx);
	}
}
