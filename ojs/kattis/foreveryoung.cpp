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
ll B = 10;
ll y, l;

void try_(ll b) {
	if(b < B) return;
	//printf("trying %lld\n", b);
	ll x = 0;
	ll yy = y;
	ll p = 1;
	while(yy) {
		if((yy % b) >= 10) break;
		x += ll(yy % b) * p;
		p *= 10;
		yy /= b;
	}
	//if(!yy) printf("got %lld >= %lld ok %d\n", x, l, x >= l);
	if(!yy && x >= l) B = max(B, b);
}

void go(ll a, ll b, ll c) {
	if(a == 0) {
		c = -c;
		if(c > 0 && b > 0 && !(c % b))
			B = max(B, c / b);
		return;
	}
	if(c > 0 && b * b - 4 * a * c < 0) return;
	typedef long double ld;
	ll sq_ = abs(sqrt<ld>(ld(b) * ld(b) - ld(4) * ld(a) * ld(c)));
	for(int i = -1000; i <= 1000; i++) {
		ll sq = sq_ + i;
		if(sq < 0) continue;
		if(!((-b + sq) % (2 * a)))
			try_((-b + sq) / (2 * a));
		if(!((-b - sq) % (2 * a)))
			try_((-b - sq) / (2 * a));
	}
}

int main() {
	scanf("%lld %lld", &y, &l);
	for(ll i = l; i <= 99; i++)
		go(0, i / 10, (i % 10) - y);
	for(ll i = max(l, 100ll); i <= 999; i++)
		go(i / 100, (i / 10) % 10, (i % 10) - y);
	for(ll b = 11; b * b * b <= y; b++)
		try_(b);
	printf("%lld\n", B);
}
