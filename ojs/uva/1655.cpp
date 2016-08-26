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
	int i, l, n, x;
	for_tests(t, tt) {
		scanf("%d %d", &l, &n);
		int mx = 0, mx2 = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			mx = max(mx, min(x, l - x));
			mx2 = max(mx2, max(x, l - x));
		}
		printf("%d %d\n", mx, mx2);
	}
}
