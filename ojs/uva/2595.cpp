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
	int i, j, p, x, n, b, h, w;
	while(scanf("%d %d %d %d", &n, &b, &h, &w) != EOF) {
		int mp = 600000;
		for(i = 0; i < h; i++) {
			scanf("%d", &p);
			bool ok = false;
			for(j = 0; j < w; j++) {
				scanf("%d", &x);
				ok |= (x >= n);
			}
			if(ok) mp = min(mp, p);
		}
		if(mp * n <= b) printf("%d\n", mp * n);
		else puts("stay home");
	}
}
