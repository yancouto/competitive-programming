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

int mdc(int a, int b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int main() {
	int i, n, x;
	for_tests(t, tt) {
		scanf("%d", &n);
		int m = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			m = mdc(x, m);
		}
		printf("%lld\n", ll(n) * ll(m));
	}
}
