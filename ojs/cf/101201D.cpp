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

ll memo[2][2][312][312][2];
inline ll& dp(int tp, int i, int lc, int ls, bool ch) {
	return memo[tp][i & 1][lc][ls][ch];
}

ll t[312];

int main() {
	ll n, k;
	scanf("%lld %lld", &n, &k);
	for(int i = 0; i < n; i++) scanf("%lld", &t[i]);
	sort(t, t + n);
	ll i, tp, lc, ls, ch;
	for(i = n + k - 2; i >= 0; i--)
		for(tp = 1; tp >= 0; tp--)
			for(lc = 0; lc <= max(0ll, n - i); lc++)
				for(ls = 0; ls <= i + 1 && ls <= k; ls++)
					for(ch = 0; ch <= 1; ch++)
	{
		ll &r = dp(tp, i, lc, ls, ch);
		r = 0;
		if(tp == 0) { // choose
			if(i >= n) r = dp(1, i, lc, ls, ch);
			else {
				r += lc * dp(1, i, lc - 1, ls + 1, ch);
				if(!ch) r += dp(1, i, lc, ls, true);
				r += (n - i - lc - !ch) * dp(1, i, lc, ls, ch);
			}
		} else { // solve
			if(i < k - 1) r = dp(0, i + 1, lc, ls, ch);
			else if(ls > 0) r = dp(0, i + 1, lc, ls - 1, ch);
			else if(!ch) r = dp(0, i + 1, lc, 0, false);
			else r = (n + k - 1 - i);
		}
		r = mod(r);
		printf("dp(%lld, %lld, %lld, %lld, %lld) = %lld\n", tp, i, lc, ls, ch, r);
	}
	for(i = 0; i < n; i++)
		printf("%lld * %lld\n", t[i], dp(0, 0, i, 0, false));
	ll tot = 0;
	for(i = 0; i < n; i++)
		tot = mod(tot + t[i] * dp(0, 0, i, 0, false));
	printf("%lld\n", tot);
}
