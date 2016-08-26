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

int a[10009], dv[10009];
int main() {
	int i, j, n, b;
	for_tests(t, tt) {
		scanf("%d", &n);
		int b = 0;
		ll tot = 0;
		int prev = 0, odd;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			if(a[i] < prev) { tot += prev - a[i]; a[i] = prev; }
			b = mdc(b, a[i]);
			prev = a[i];
		}
		if(b > 1) { printf("%lld\n", tot); continue; }
		ll mn = LLONG_MAX;
		for(i = 2; i <= 10000; i++)
			if(!dv[i]) {
				for(j = i * i; j <= 10000; j += i)
					dv[j] = 1;
				ll tot2 = 0;
				for(j = 0; j < n; j++)
					if(a[j] % i)
						tot2 += i - (a[j] % i);
				mn = min(mn, tot + tot2);
			}
		printf("%lld\n", mn);
	}
}
