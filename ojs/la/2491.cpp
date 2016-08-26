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
#ifndef ONLINE_JUDGE
#	define debug(args...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");}
#else
#	define debug(args...) {}
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n, k, a[103], all;

int memo[103][103][9][257];
int solve(int i, int l, int h, int bm) {
	if(i == n) return __builtin_popcount(bm ^ all);
	int &m = memo[i][l][h][bm];
	if(m != -1) return m;
	m = INT_MAX;
	if(l > 0) m = solve(i + 1, l - 1, h, bm);
	m = min(m, (a[i] != h) + solve(i + 1, l, a[i], bm | (1 << a[i])));
	return m;
}


int main() {
	int i, t = 0;
	while(true) {
		scanf("%d %d", &n, &k);
		if(!n) return 0;
		all = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			a[i] -= 25;
			all |= (1 << a[i]);
		}
		memset(memo, -1, sizeof memo);
		printf("Case %d: %d\n\n", ++t, solve(0, k, 8, 0));
	}
}
