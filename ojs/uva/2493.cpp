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
	int i, k, xx, yy, x, y;
	while(true) {
		scanf("%d", &k);
		if(!k) return 0;
		scanf("%d %d", &xx, &yy);
		for(i = 0; i < k; i++) {
			scanf("%d %d", &x, &y);
			if(x == xx || y == yy) puts("divisa");
			else if(y > yy && x > xx) puts("NE");
			else if(y > yy && x < xx) puts("NO");
			else if(y < yy && x > xx) puts("SE");
			else puts("SO");
		}
	}
}
