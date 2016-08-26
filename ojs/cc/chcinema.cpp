// WA
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

ll rows(ll num, ll size, ll &b, ll &z) {
	ll each = (size + 1) / 2;
	ll pb = min(b, each * num);
	b -= pb;
	ll pz = min(z, size * num - pb);
	z -= pz;
	return pb + pz;
}

int main() {
	int i; ll n, m, z, l, r, b, tot;
	for_tests(t, tt) {
		scanf("%lld %lld %lld %lld %lld %lld", &n, &m, &z, &l, &r, &b);
		l += r; r = 0;
		tot = 0;
		ll c = min(m, l / n);
		if(c && c != m && !((m - c) & 1)) c--;
		m -= c; tot += n * c;
		l -= n * c;
		if(m == 0) { printf("%lld\n", tot); continue; }
		if(m == 1) { printf("%lld\n", tot + min(n, z + l + b)); continue; }
		if(m & 1) {
			tot += l;
			tot += rows(l / 2, m - 2, b, z);
			if(l & 1) tot += rows(1, m - 1, b, z);
			tot += rows(n - ((l + 1) / 2), m, b, z);
		} else {
			tot += l;
			tot += rows(l, m - 1, b, z);
			tot += rows(n - l, m, b, z);
		}

		printf("%lld\n", tot);
	}
}
