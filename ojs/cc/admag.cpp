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
		ull n;
		scanf("%llu", &n);
		ull f1 = 0, f2 = 1; int i;
		for(i = 0; f2 <= n; i++) {
			ull f3 = f2 + f1;
			f1 = f2; f2 = f3;
		}
		printf("%d\n", i - 1);
	}
	return 0;
}
