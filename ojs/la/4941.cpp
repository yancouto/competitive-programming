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


int main() {
	for_tests(tn, tt) {
		ll n, x;
		scanf("%lld", &n);
		for(x = 1; 2ll * n - x * x - x > 0; x++) {
			ll top = 2ll * n - x * x - x;
			if(!(top % (2ll * (x + 1ll)))) {
				ll a = top / (2ll * (x + 1ll));
				printf("%lld = %lld", n, a);
				for(int i = 1; i <= x; i++)
					printf(" + %lld", a + i);
				putchar('\n');
				break;
			}
		}
		if(2ll * n - x * x - x <= 0) puts("IMPOSSIBLE");
	}
}
