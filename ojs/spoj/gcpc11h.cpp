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
inline int count_1s(int x) { return __builtin_popcount(x); }
inline int count_1s(ull x) { return __builtin_popcountll(x); }
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n;
ll t;
int c[100009][2][2];

ll memo[100009][2][2];
ll solve(int i, int be, int fbe) {
	ll &m = memo[i][be][fbe];
	if(m != -1) return m;
	if(i == n - 1) m = c[i][!be][fbe];
	else m = min(solve(i + 1, 0, fbe) + c[i][!be][0], solve(i + 1, 1, fbe) + c[i][!be][1]);
	return m;
}

void build(int i, int be, int fbe) {
	putchar(be? 'B' : 'F');
	if(i < n - 1) {
		if((c[i][!be][0] + solve(i + 1, 0, fbe)) < (c[i][!be][1] + solve(i + 1, 1, fbe)))	
			build(i + 1, 0, fbe);
		else
			build(i + 1, 1, fbe);
	}
}

int main() {
	int i, j, x;
	for_tests(tt, ttt) {
		scanf("%d %lld", &n, &t);
		for(i = 0; i < n; i++) {
			scanf("%d", &x); t -= x;
			for(j = 0; j < 2; j++)
				for(x = 0; x < 2; x++) {
					memo[i][j][x] = -1;
					scanf("%d", &c[i][j][x]);
				}
		}
		if(t < 0) { puts("IMPOSSIBLE"); continue; }
		if(solve(0, 0, 0) > t && solve(0, 1, 1) > t) { puts("IMPOSSIBLE"); continue; }
		if(solve(0, 0, 0) < solve(0, 1, 1))	build(0, 0, 0);
		else build(0, 1, 1);
		putchar('\n');
	}
	return 0;
}
