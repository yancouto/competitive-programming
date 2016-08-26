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

pii p[501 * 501];
int main() {
	int i, j, n, x;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				scanf("%d", &x);
				p[x-1] = pii(i, j);
			}
		ll d = 0;
		for(i = 1; i < n*n; i++)
			d += abs(p[i].fst - p[i-1].fst) + abs(p[i].snd - p[i-1].snd);
		printf("%lld\n", d);
	}
}
