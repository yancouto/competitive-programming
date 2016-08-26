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
	for_tests(t, tt) {
		int n, i; ld p;
		scanf("%d %Lf", &n, &p); n--;
		ld ans = 1;
		for(i = 1; i <= n; i <<= 1) {
			if(i & n) ans *= p;
			p *= p;
		}
		ld o = 1000000000 * ans;
		ans = 1000000000 - o;
		if(!(n & 1)) swap(o, ans);
		printf("%Lf %Lf %Lf\n", ans, o, ans + o);
	}
}
