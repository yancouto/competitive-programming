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
	int i, n;
	ll x;
	for_tests(t, tt) {
		scanf("%d %lld", &n, &x);
		ll tot = 0;
		ll cur2 = 1;
		ll sum = mod(x << 1);
		for(i = 0; i < n; i++) {
			scanf("%lld", &x);
			cur2 = mod(cur2 << 1);
			tot = mod((tot << 1) + sum * x);
			sum = mod(sum + cur2 * x);
		}
		printf("%lld\n", tot);
	}
}
