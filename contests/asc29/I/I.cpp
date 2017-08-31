#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

ll d, b, t, p;

ll cll (ll p, ll q){
	return (p+q-1)/q;
}

ll getp (ll s) {
	return cll(t*(b-d), s);
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("video.in", "r", stdin);
	freopen("video.out", "w", stdout);
#endif
	scanf("%lld %lld %lld %lld", &d, &b, &t, &p);

	ll hi = p*d;
	ll lo = 1;
	ll pts = getp(hi);
	while (lo < hi) {
		ll md = (lo + hi)/2;

		if (getp(md) > pts)
			lo = md + 1;
		else
			hi = md;
	}

	printf("%lld\n", lo);
}
