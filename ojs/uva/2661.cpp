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

int main() {
	ll x;
	for_tests(t, tt) {
		scanf("%lld", &x);
		ll l = 0, r = 2000000000;
		while(l < r) {
			ll m = (l + r + 1) / 2ll;
			if((m * (m + 1ll)) / 2ll > x) r = m - 1;
			else l = m;
		}
		printf("%lld\n", l);
	}
}
