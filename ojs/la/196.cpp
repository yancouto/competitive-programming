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
	ull b, n;
	while(true) {
		scanf("%llu", &n);
		if(!n) return 0;
		if(n == 1) { puts("1 0"); continue; }
		int tot = 1;
		for(b = 2; b * b < n; b++) {
			if(!(n % b)) {
				tot += 2;
				ull aux = n / b;
				while(!(aux % b)) tot++, aux /= b;
			}
		}
		if(b * b == n) tot += 2;
		printf("%llu %d\n", n, tot);
	}
}
