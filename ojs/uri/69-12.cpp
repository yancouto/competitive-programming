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

int main() {
	int n, i; ll x, y, cx, cy, r1, r2; pii v[2];
	while(true) {
		if(scanf("%d", &n) == EOF) return 0;
		if(!n) return 0;
		v[0] = v[1] = pii(0, 0);
		scanf("%lld %lld %lld %lld", &cx, &cy, &r1, &r2);
		for(i = 0; i < 2*n; i++) {
			scanf("%lld %lld", &x, &y);
			ll d = (x - cx) * (x - cx) + (y - cy) * (y - cy);
			if(d < r1 * r1) v[i & 1].fst++;
			else if(d <= r2 * r2) v[i & 1].snd++;
		}
		if(v[0] > v[1]) puts("C > P");
		else if(v[0] < v[1]) puts("P > C");
		else puts("C = P");
	}
}
