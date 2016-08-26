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
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int a[60];
ll v[18][(1 << 16) + 10];
int sz[18];

int main() {
	int n, k, i, j, x; ll A, B;
	scanf("%d %d %lld %lld", &n, &k, &A, &B);
	for(i = 0; i < n; i++) {
		scanf("%d", &x); a[i] = 1;
		for(j = 2; j * j <= x; j++) {
			if(x % j) continue;
			a[i] *= j;
			while(!(x % j)) x /= j;
		}
		if(x > 1) a[i] *= x;
	}
	if(n == 1) {
		printf("%d\n", a[0] >= A && a[0] <= B);
		return 0;
	}
	int l = (n + 1) / 2;
	for(i = 0; i < (1 << l); i++) {
		ll val = 0;
		for(j = 0; j < l; j++)
			val += (!!(i & (1 << j))) * a[j];
		int nu = __builtin_popcount(i);
		v[nu][sz[nu]++] = val;
	}
	for(i = 0; i < 18; i++)
		sort(v[i], v[i] + sz[i]);
	int r = n / 2;
	ll tot = 0;
	for(i = 0; i < (1 << r); i++) {
		ll val = 0;
		for(j = 0; j < r; j++)
			val += (!!(i & (1 << j))) * a[j + l];
		int nu = __builtin_popcount(i);
		for(j = k - nu; j >= 0; j--)
			tot += upper_bound(v[j], v[j] + sz[j], B - val) - lower_bound(v[j], v[j] + sz[j], A - val);
	}
	printf("%lld\n", tot);
}
