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
const int MAX = 505;
int n, m;
int blog[MAX][MAX], yeye[MAX][MAX];
int memo[MAX][MAX];
int solve(int i, int last) {
	if(i == m) return 0;
	int &r = memo[i][last];
	if(r != -1) return r;
	if(last) r = solve(i + 1, last) + blog[last - 1][i] + yeye[last][i];
	else r = solve(i + 1, last) + yeye[last][i];
	if(last < n) r = max(r, solve(i, last + 1));
	return r;
}

int main() {
	int i, j;
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf("%d", &yeye[i][j]);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf("%d", &blog[i][j]);
		for(j = 0; j < m; j++)
			for(i = 1; i < n; i++)
				blog[i][j] += blog[i - 1][j];
		for(j = 0; j < m; j++) {
			for(i = n - 2; i >= 0; i--)
				yeye[i][j] += yeye[i + 1][j];
			yeye[n][j] = 0;
		}
				
		memset(memo, -1, sizeof memo);
		printf("%d\n", solve(0, 0));
	}
}
