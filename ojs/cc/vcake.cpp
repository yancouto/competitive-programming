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

ll a[3];
bool go(ll r, ll c) {
	if(a[0] % r) return false;
	c -= a[0] / r;
	if(!(a[1] % r) && !(a[2] % r)) return true;
	if(!(a[1] % c) && !(a[2] % c)) return true;
	return false;
}

int main() {
	ll r, c;
	for_tests(t, tt) {
		scanf("%lld %lld %lld %lld %lld", &r, &c, &a[0], &a[1], &a[2]);
		if(r * c != a[0] + a[1] + a[2]) { puts("No"); continue; }
		sort(a, a + 3);
		bool any = false;
		do {
			any |= go(r, c);
			any |= go(c, r);
		} while(next_permutation(a, a + 3));
		if(any) puts("Yes");
		else puts("No");
	}
}
