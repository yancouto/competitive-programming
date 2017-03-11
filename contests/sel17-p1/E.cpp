#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;

const int N = 212345;
int a[N], nmx[N], nmn[N];

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll fexp(ll a, ll b) {
	ll r = 1;
	for(; b; b >>= 1, a = mod(a * a))
		if(b & 1)
			r = mod(r * a);
	return r;
}

inline ll choose0(ll n) {
	return fexp(2ll, n);
}

inline ll choose1(ll n) {
	return mod(choose0(n) - 1 + modn);
}

int main() {
	int i, t, n, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		int mx = *max_element(a, a + n), cmx = 0;
		int mn = *min_element(a, a + n), cmn = 0;
		nmx[n] = nmn[n] = n;
		for(i = n - 1; i >= 0; i--) {
			if(a[i] == mx) cmx++, nmx[i] = i;
			else nmx[i] = nmx[i + 1];
			if(a[i] == mn) cmn++, nmn[i] = i;
			else nmn[i] = nmn[i + 1];
		}
		if(mx == mn) {
			printf("%lld %lld\n", mod((ll(n) * ll(n + 1)) / 2ll), choose1(n));
			continue;
		}
		ll tot = 0;
		for(i = 0; i < n; i++) {
			int j = max(nmn[i], nmx[i]);
			if(j == n) break;
			tot = mod(tot + (n - j));
		}
		ll sub = mod(mod(choose1(cmx) * choose1(cmn)) * choose0(n - cmx - cmn));
		printf("%lld %lld\n", tot, sub);
	}
}
