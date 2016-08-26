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

ll memo[25][2][2];
char str[25];
ll solve(int d, bool pre, bool one) {
	if(!str[d]) return 1;
	ll &r = memo[d][pre][one];
	if(r != -1) return r;
	r = 0;
	for(int i = 0; i <= 9; i++) {
		if(pre && (i + '0') > str[d]) break;
		if(i == 4 || (one && i == 3)) continue;
		r += solve(d + 1, pre && (i + '0') == str[d], i == 1);
	}
	return r;
}

int main() {
	ull n;
	while(scanf("%llu", &n) != EOF) {
		ull l = 0, r = 10000000000000000000ull;
		//sprintf(str, "%llu", n);
		//memset(memo, -1, sizeof memo);
		//printf("%lld\n", solve(0, true, false) - 1);
		while(l < r) {
			ull m = ((r - l) / 2ull) + l;
			sprintf(str, "%llu", m);
			memset(memo, -1, sizeof memo);
			if(solve(0, true, false) < n + 1) l = m + 1;
			else r = m;
		}
		printf("%llu\n", l);
	}
}
