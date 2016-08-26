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
	ll n, c;
	for_tests(t, tt) {
		scanf("%lld %lld", &n, &c);
		if(n == 1) { puts("Yes"); continue; }
		if(n == 2) {
			if(c < 3) puts("No");
			else puts("Yes");
			continue;
		}
		if(n & 1) {
			if(c % n) { puts("No"); continue; }
			c /= n;
			if(((n - 1) % 2) == 0) {
				ll g = (n - 1ll) / 2ll;
				if(c - g >= 1) puts("Yes");
				else puts("No");
			} else {
				if(c - (n - 1) >= 1) puts("Yes");
				else puts("No");
			}
		} else {
			if(c % (n / 2)) { puts("No"); continue; }
			c /= (n / 2ll);
			if(c & 1ll) {
				if(c - (n - 1) >= 2) puts("Yes");
				else puts("No");
			} else {
				if(c - 2ll*(n-1) >= 2) puts("Yes");
				else puts("No");
			}
		}
		//if(2*c <= n) { puts("No"); continue; }
		//if((n - 1ll) % 2 == 0) { puts("Yes"); continue; }
		//if(2*(n - 1ll) < 2 * c) { puts("Yes"); continue; }
		//puts("No");
	}
}
