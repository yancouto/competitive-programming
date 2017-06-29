#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll qt[2][2][312][312][2];
inline ll& q(int k, int i, int lc, int ls, int has) {
	return qt[k][i & 1][lc][ls][has];
}

ll t[312];

int main () {
	int i, n, K;
	scanf("%d %d", &n, &K);
	for(i = 0; i < n; i++) scanf("%lld", &t[i]);

	ll k, lc, ls, has;
	for(i = n - 1 + K - 1; i >= 0; i--)
		for(k = 1; k >= 0; k--)
			for(lc = 0; lc <= max(0, n - i); lc++)
				for(ls = 0; ls <= i + 1 && ls <= n; ls++)
					for(has = 0; has <= 1; has++)
	{
		ll &r = q(k, i, lc, ls, has);
		if(k == 0) {
			if(i >= n) r = q(1, i, lc, ls, has);
			else {
				r  = mod(lc * q(1, i, lc - 1, ls + 1, has));
				if(!has) r = mod(r + q(1, i, lc, ls, true));
				r = mod(r + ll((n - i) - lc - (!has)) * q(1, i, lc, ls, has));
				r = mod(r);
			}
		} else {
			if(i < K - 1) r = q(0, i + 1, lc, ls, has);
			else if(ls > 0) r = q(0, i + 1, lc, ls - 1, has);
			else if(!has && ls == 0) r = q(0, i + 1, lc, 0, false);
			else if(has && ls == 0) r = n + K - 1 - i;
			else abort();
		}
		printf("%d [%d][%d][%d][%d] = %lld\n", k, i, lc, ls, has, r);
	}
	ll tot = 0;
	sort(t, t + n);
	for(i = 0; i < n; i++)
		printf("%lld * %lld\n", t[i], q(0, 0, i, 0, false));
	for(i = 0; i < n; i++)
		tot = mod(tot + t[i] * q(0, 0, i, 0, false));
	printf("%lld\n", tot);
}
