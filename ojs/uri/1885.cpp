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

ull mdc(ull a, ull b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int main() {
	for_tests(t, tt) {
		int k, i;
		ull n, f;
		scanf("%llu %d", &n, &k);
		for(i = 0; i < k; i++) {
			scanf("%llu", &f);
			while(true) {
				ull a = mdc(n, f);
				if(a == 1) break;
				while(!(n % a)) n /= a;
			}
		}
		if(n == 1) puts("Y");
		else puts("N");
	}
}
