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

pii operator + (pii a, pii b) { return pii(a.fst + b.fst, a.snd + b.snd); }

typedef long double ld;

pii f[112];

int main() {
	int n;
	f[0] = pii(1, 0);
	f[1] = pii(0, 1);
	for(int i = 2; i < 44; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}
	for_tests(tn, tt) {
		scanf("%d", &n);
		ll A = (n / 2), B = ((n + 1) / 2);
		for(int i = 43; i >= 3; i--) {
			//printf("i = %d\n", i);
			if(f[i].fst + f[i].snd > n) continue;
			ll f = ::f[i].fst, s = ::f[i].snd;
			//printf("(%lld, %lld)\n\n", f, s);
			for(ll a = 1; a <= B; a++) {
				//printf("a = %lld\n", a);
				//printf("%lld > %lld\n", a * s, n - a * f);
				//system("sleep .1");
				if(a * s > n - a * f) break;
				if((n - a * f) % s) continue;
				ll b = (n - a * f) / s;
				assert(b >= a);
				assert(a * f + b * s == n);
				if(b < B || (b == B && a < A))
					A = a, B = b;
			}
		}
		printf("%lld %lld\n", A, B);
	}

}
