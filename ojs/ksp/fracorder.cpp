#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 512345;

ll p[N];

ll leq(ll n, ll a, ll b) {
	for(ll q = 1; q <= n; q++)
		p[q] = (a * q) / b;
	for(ll q = 1; q <= n; q++)
		for(ll qq = q + q; qq <= n; qq += q)
			p[qq] -= p[q];
	return accumulate(p + 1, p + n + 1, 0ll);
}

ll gcd(ll a, ll b) {
	if(!b) return a;
	return gcd(b, a % b);
}

int main() {
	while(true) {
		int op; ll n, a, b;
		scanf("%d", &op);
		if(op == 2) break;
		scanf("%lld", &n);
		if(op == 1) {
			scanf("%lld %lld", &a, &b);
			ll g = gcd(a, b);
			a /= g;
			b /= g;
			if(b > n || a > b) { puts("fail"); continue; }
			printf("%lld\n", leq(n, a, b) + 1);
		} else {
			ll x;
			scanf("%lld", &x);
			if(x == 1) { puts("0/1"); continue; }
			ll tot = leq(n, 1, 1);
			if(x - 1 > tot) { puts("fail"); continue; }
			x--;
			ll l = 0, r = n;
			while(l < r) {
				ll m = (l + r + 1) / 2;
				if(leq(n, m, n) < x) l = m;
				else r = m - 1;
			}
			vector<pii> nxt;
			if(l != n) nxt.pb(pii(l + 1, n));
			ll k = x - leq(n, l, n) - 1ll;
			for(ll q = 1; q <= n; q++) {
				if((l * q) / n != q) {
					ll p = (l * q) / n + 1ll;
					if(gcd(p, q) == 1)
						nxt.pb(pii(p, q));
				}
			}
			nth_element(nxt.begin(), nxt.begin() + k, nxt.end(), [](pii a, pii b) { return a.fst * b.snd <= a.snd * b.fst; });
			printf("%lld/%lld\n", nxt[k].fst, nxt[k].snd);
		}
	}
}
