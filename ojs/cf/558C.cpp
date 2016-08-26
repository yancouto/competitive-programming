// WAAAAAAA
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n, a[100009];
int p2time[100009];
int p2i[100009];

int mdc(int x, int y) {
	if(y == 0) return x;
	return mdc(y, x % y);
}

inline bool isp2(int x) { return !(x & (x - 1)); }
int p2n(int x) {
	int j;
	for(j = 0; (1 << j) < x; j++);
	return j;
}

int main() {
	int m = 0, i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		m = mdc(a[i], m);
	}
	int old_m = m; int cont = 0;
	while(true) {
		for(i = 0; i < n; i++) {
			if(!isp2(a[i] / m)) {
				debug("%d to %d (%d to %d)", a[i], a[i]/2, m, mdc(m, a[i]/2));
				a[i] >>= 1;
				m = mdc(m, a[i]);
				cont++;
				break;
			}
		}
		if(i < n) { old_m = m; continue; }
		if(m == old_m) break;
		old_m = m;
	}
	ll mn = LLONG_MAX;
	for(i = 0; (1 << i) <= 1000000; i++) {
		ll acc = 0;
		for(j = 0; j < n; j++) {
			acc += abs(p2n(a[j] / m) - i);
		}
		mn = min(mn, acc);
	}
	printf("%lld\n", mn + cont);
}